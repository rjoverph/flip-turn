<?php
/**
 * IP class
 * 
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 */

/**
 * Class for managing
 * IP addresses
 *
 * @author Suren Markosian
 * @package phpHtmlLib-framework
 */
class IP {

    /**
     * Wrapper functions that converts an IP to a long and reverse.
     * Ensures that order is respected (ie 65.0.0.0 < 224.0.0.0),
     * which ip2long doesn't do...
     *
     * @param string $ip
     */
    static public function ip2int($ip) {
        return sprintf("%u",ip2long($ip));
    }

    /**
     * Wrapper functions that converts an IP to a long and reverse.
     * Ensures that order is respected (ie 65.0.0.0 < 224.0.0.0),
     * which ip2long doesn't do...
     *
     * @param int $n
     */
    static public function int2ip($n) {
        return long2ip(-(4294967296-$n));
    }

    /**
     * Returns true IP of the client
     *
     * @return string
     *
     * @author Suren Markosian
     *
     */
    static public function get_client_ip($use_proxy = true) {

        if ($use_proxy && isset($_SERVER['HTTP_X_FORWARDED_FOR']) &&
            substr($_SERVER['HTTP_X_FORWARDED_FOR'], 0, 3) != "10." &&
            substr($_SERVER['HTTP_X_FORWARDED_FOR'], 0, 4) != "192.") {
            $ip = trim(array_pop(explode(",", $_SERVER['HTTP_X_FORWARDED_FOR'])));

            $long_ip = ip2long($ip);
            if ($long_ip == -1 || !$long_ip) {
                // validate this ip
                // and revert back to original ip
                $ip = $_SERVER['REMOTE_ADDR'];
            }

        }
        else {
            $ip = $_SERVER['REMOTE_ADDR'];
        }

        return $ip;
    }


}

?>
