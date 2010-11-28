<?php
/**
 * NetworkValidator class used to validate
 * 'network' data fields in our application
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Validation
 */


/**
 * This child of Validator is responsible for
 * containing the methods related to 'networking'.
 * Such as urls, emails, ip addresses and such.
 *
 * @author Walter A. Boring IV
 * @package phpHtmlLib-framework
 * @subpackage Validation
 */
class NetworkValidator extends Validator {

    /**
     * This method tests a string as a valid
     * hostname value or a valid email string
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_hostemail($name) {
        if ( strchr($name, "@") ) {
            self::is_email($name);
        } else {
            self::is_hostname($name);
        }
    }

    /**
     * This function validates a single email address.
     * It supports email addresses in the format of
     * jane@blah.com or "Jane Doe <jane@blah.com>"
     *
     * @param string - the value to validate
     * @param bool - allows long email name format
     * @return void
     */
    public static function is_email($email, $allow_name = true) {

        //no quotes allowed
        if ( strstr($email, '"') || strstr($email, "'") ) {
            self::error(phphtmllibException::STR_INVALID_EMAIL);
        }

        //lets see if the email is in the form of
        //"Foo Bar <foo@bar.com>"
        $name = explode(" ", $email);
        if ( count($name) > 1 ) {

            if (!$allow_name) {
                self::error(phphtmllibException::STR_INVALID_EMAIL);
            }

            //it looks like they gave us an email
            //with a leading name such as Foo Bar <foo@bar.com>
            //find the email address inside <>
            $found_email = FALSE;
            foreach( $name as $key => $val ) {
                if ( strstr($val, "@") ) {
                    $found_email = TRUE;
                    if ( (substr($val, 0, 1) == "<") && (substr($val, strlen($val)-1, 1) == ">") ) {
                        $email = substr($val, 1, strlen($val)-2 );
                    } else {
                        //invalid email address
                        //it must have a <
                        self::error(phphtmllibException::STR_INVALID_EMAIL_MISSING_BRACKETS);
                    }
                }
            }
            if ( !$found_email ) {
                //we couldn't find an email address
                //in the text.
                self::error(phphtmllibException::STR_INVALID_EMAIL);
            }
        }

        self::is_alphanum($email, "@.-_/:",phphtmllibException::STR_INVALID_EMAIL);

        // "@.", ".@.", "_@.", .com, .net, .edu, .blah
        if ( !ereg("^( )*([a-zA-Z0-9_/:]|\\-|\\.)+@(([a-zA-Z0-9_]|\\-)+\\.)+[a-zA-Z]{2,4}$", $email, $arr) ) {
            self::error(phphtmllibException::STR_INVALID_EMAIL);
        }

        $len = strlen($email);
        if ( $len > self::VALIDATE_EMAIL_LENGTH ) {
            self::error(phphtmllibException::STR_INVALID_LENGTH_256);
        }

        // email cannot end with a dot
        if ( ereg("\.$", $email) ) {
            self::error(phphtmllibException::STR_INVALID_EMAIL);
        }

        // no space
        if ( ereg(" ", $email, $arr) ) {
            self::error(phphtmllibException::STR_INVALID_EMAIL);
        }

    }

    /**
     * This function tests a string that may
     * contain many email addresses seperated by
     * commas
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_manyemails( $emails ) {
        //first lets get the list of emails

        $email_arr = explode(",", $emails);
        foreach( $email_arr as $key => $email) {
            self::is_email(trim($email));
        }
    }

    /**
     * This method validates a string as a valid url
     * It inclues the prefix, hostname/ip, port number
     * and path.
     *
     * NOTE: format is in
     *       [http://] hostip [:port number] [path]
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_url($url) {
        // The first few characters could be http://. If so, remove them
        $url = ereg_replace("^http(s)?:\/\/", "", $url);

        // Get the location of first : or '/'
        $len = strcspn($url, ":\/");
        $host = substr($url, 0, $len);
        self::is_hostip($host);

        $rest = substr($url, $len);

        // Extract and verify the port number, if specified.
        if ( ereg("^(:)([^\/]*)(.*)", $rest, $regs) ) {
            $port_num = $regs[2];
            self::is_num($port_num, '', phphtmllibException::INT_INVALID_PORT_NUM);
            $rest = $regs[3];
        }

        // The path field may be null
        if ( ereg("^[[:space:]]*$", $rest) ) {
            return TRUE;
        }

        self::is_urlpath($rest);
    }

    /**
     * This method validates a strict url.
     * It is the same as is_url, except that it requires
     * the prefix http://
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_strict_url($url) {
        $decoded_url = parse_url( $url );
        if ( !isset($decoded_url['scheme']) || !$decoded_url['scheme'] ) {
            //looks like they didn't provide the scheme
            self::error(phphtmllibException::STR_INVALID_URL);
        }
        self::is_url($url);
    }

    /**
     * This method validates a string as a valid
     * url path to a file
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_urlpath ($path) {
        //   DOS related checks are also needed
        self::is_alphanum($path, "-_/:.,%?&=", phphtmllibException::STR_INVALID_PATH_CHARACTERS);
    }

    /**
     * This is just a wrapper for is_domainname
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_hostname ($name) {
        self::is_partial_domainname($name);
    }

    /**
     * This validates a string as an IP address
     * This should work with either IPv4 or IPv6
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_ip ($ip) {

        self::is_num($ip, ".", phphtmllibException::STR_INVALID_IP);

        if ( $ip == "0.0.0.0" ) {
            self::error(phphtmllibException::STR_INVALID_IP);
        }

        $regs = split("\.", $ip);
        $num = sizeof($regs);

        // Allow IPv4 and IPv6
        if ( $num != 4 && $num != 8 ) {
            self::error(phphtmllibException::STR_INVALID_IP);
        }

        for ( $i = 0; $i < $num; ++$i ) {
            self::is_num($regs[$i], '', phphtmllibException::STR_INVALID_IP);

            if ( ($regs[$i] >= 256) || ($regs[$i] == "") ) {
                self::error(phphtmllibException::STR_INVALID_IP);
            }
        }
    }
    
    /**
	 * This tries to validate an ip address as an IPv6
	 * specific ip.
	 * 
	 * @param string = the value to validate
	 * @return void
	 */
    public static function is_ip_v6($ip) {
    	//try and use filter_var if we have it
    	//requires php 5.2.0 or >
    	if (function_exists("filter_var")) {
    	   	if(filter_var($ip, FILTER_VALIDATE_IP, FILTER_FLAG_IPV6) === FALSE) {
    			self::error(phphtmllibException::STR_INVALID_IP);    	    
    		} else {
    		    return true;
    		}
    	} else {    
    		if (substr_count($value, ":") < 2) {
    			// has to contain ":" at least twice like in ::1 or 1234::abcd
    			self::error(phphtmllibException::STR_INVALID_IP);
    		}
    		if (substr_count($value, "::") > 1) {
    			//only 1 double colon allowed.
    			self::error(phphtmllibException::STR_INVALID_IP);
    		}
    	
    		$groups = explode(':', $value);
    		$num_groups = count($groups);
    		if (($num_groups > 8) || ($num_groups < 3)) {
	    		//3-8 groups of 0-4 digits (1 group has to be at leas 1 digit)
    			self::error(phphtmllibException::STR_INVALID_IP);
    		}
		
    		$empty_groups = 0;
			foreach ($groups as $group) {
				$group = trim($group);
				if (!empty($group) && !(is_numeric($group) && ($group == 0))) {
					if (!preg_match('#([a-fA-F0-9]{0,4})#', $group)) {
						self::error(phphtmllibException::STR_INVALID_IP);
					}
				} else {
					++$empty_groups;
				}
			}
		
			if ($empty_groups >= $num_groups) {
				self::error(phphtmllibException::STR_INVALID_IP);		
			}
    	}
	}

    /**
     * This validates a string as a portion
     * of an  IP address.
     * This should work with either IPv4 or IPv6
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_partial_ip($ip) {
        self::is_num($ip, ".",phphtmllibException::STR_INVALID_IP);

        $regs = split("\.", $ip);
        $num = sizeof($regs);

        // Allow IPv4 and IPv6
        if ( $num > 8 ) {
            self::error(phphtmllibException::STR_INVALID_IP);
        }

        for ( $i = 0; $i < $num; ++$i ) {
            self::is_num($regs[$i] + 0, '', phphtmllibException::STR_INVALID_IP);

            if ( $regs[$i] >= 256 ) {
                self::error(phphtmllibException::STR_INVALID_IP);
            }
        }

    }

    /**
     * This method tries to validate a string
     * as a valid IP address or a hostname
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_hostip($hostip) {

        // If it looks like a number, check if it is a valid ip, else
        // check if it is a valid name.
        try {
            self::is_num($hostip, ".");
            self::is_ip($hostip);
        } catch (ValidatorException $e) {
            self::is_hostname($hostip);
        }

    }


    /**
     * This method tries to validate a string
     * as a MAC address in the format of
     * xx:xx:xx:xx:xx:xx
     *
     * @param string $mac
     * @return void
     */
    public static function is_mac_address($mac) {
        self::is_alphanum($mac, ":");

    }


    /**
     * This method validates a string for a valid
     * hostname for a machine.
     *
     * @param string - the value to validate
     */
    public static function is_domainname ($name, $forbid_www=FALSE) {
        if (!ereg( "^(([A-Za-z0-9]{1,63}|".
               "([A-Za-z0-9][A-Za-z0-9\-]{1,61}[A-Za-z0-9]))\.)+".
               "[A-Za-z]{2,63}$", $name )) {
            self::error(phphtmllibException::STR_INVALID_HOST_NAME);
        } else if ($forbid_www && ereg( "^www\.", $name )) {
            self::error(phphtmllibException::STR_INVALID_HOST_NAME);
        }
    }

    /**
     * This method validates a string for a valid
     * partial hostname for a machine.
     *
     * @param string - the value to validate
     */
    public static function is_partial_domainname($name) {

        // letters, digits and ".-" only
        self::is_alphanum($name, ".-", phphtmllibException::STR_INVALID_HOST_NAME);

        $len = strlen($name);
        if ( $len > self::VALIDATE_MAX_HOSTNAME_LENGTH ) {
            self::error(phphtmllibException::STR_INVALID_LENGTH);
        }

        // Error if it contains no alphabets
        if ( !eregi("[a-z]", $name) ) {
            self::error(phphtmllibException::STR_INVALID_HOST_NAME);
        }

    }


    /**
     * Validate domain
     * Will check if a domain is valid
     *
     * @param string - the value to validate
     * @param boolean $allow_www - allow www prefix?
     * @param int phphtmllibException error code
     * @return void
     */
    public static function is_valid_domain($domain_value, $allow_www=false, $err=NULL) {

        // we allow 'none' as empty domain
        if ( $domain_value=='none' ) return TRUE;

        if ($err == NULL) {
            $err = phphtmllibException::STR_INVALID_DOMAIN_NAME;
        }

        // allow uppercase domains
        $domain_value = strtolower($domain_value);

        if ( !ereg( "^(([a-z0-9]{1,63}|([a-z0-9][a-z0-9\-]{1,61}[a-z0-9]))\.)+[a-z]{2,4}$", $domain_value) ) {
            self::error($err, $domain_value . " is not RFC compliant");
        } else if ( !$allow_www && ereg( "^www\.", $domain_value) ) {
            self::error($err, $domain_value . " is invalid.");
        }
    }

    /**
     * Test to see if a string is a valid
     * hostname
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_host($host) {
        self::is_valid_domain($host, TRUE, phphtmllibException::STR_INVALID_HOST_NAME);
    }

    /**
     * validate a list of hosts.
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_hostlist($hostlist) {
        $a = explode(",", str_replace(" ", "", $hostlist));
        foreach ($a as $host) {
            self::is_host($host);
        }
    }


    /**
     * this method tests to see if this is a valid
     * hostname value minus the domain name portion.
     *
     * @param string - the value to validate
     * @return void
     */
    public static function is_standalone_hostname ($name) {

        // letters, digits and "-" only
        self::is_alphanum($name, "-", phphtmllibException::STR_INVALID_STANDALONE_HOST_NAME);

        $len = strlen($name);
        if ( $len > self::VALIDATE_MAX_HOSTNAME_ELEMENT_LENGTH ) {
            self::error(phphtmllibException::STR_INVALID_LENGTH);
        }

        // Error if it doesn't start with an alphabet or digit
        if ( !eregi("^[a-z0-9]", $name) ) {
            self::error(phphtmllibException::STR_INVALID_HOST_NAME);
        }

        // Error if it contains no alphabets
        if ( !eregi("[a-z]", $name) ) {
            self::error(phphtmllibException::STR_INVALID_HOST_NAME);
        }
    }

}

?>
