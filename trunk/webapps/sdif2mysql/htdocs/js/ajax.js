/**
 * This file uses prototype and
 * scriptaculous to do it's internal work.
 *
 * @author Walter A. Boring IV
 * @link http://www.prototypejs.org/
 * @link http://script.aculo.us/
 */

/**
 * Ajax GET request to a url.
 * Don't do anything with results.
 * 
 * This is usefull for just simple pings
 * of data back to the server.
 * 
 * @param string url
 */
function ar_g(url) {
    new Ajax.Request(url, {method:'get',asynchronous:true});
}

/**
 * Ajax GET request to a url.
 * The results
 * of the request are passed to m_s() (message_show) 
 * and e_s() (error_show)
 *
 * @param string url
 */
function ar_g_message(url) {
    ar_g_s_f(url, m_s, e_s);
}

/**
 * AJAX GET request with success and failure functions.
 * The success function process the success
 * and the failure function process the failure if it
 * fails.
 *
 * @param string url
 * @param string s (success function)
 * @param string f (failure function)
 */
function ar_g_s_f(url, s, f) {
    new Ajax.Request(url, {method:'get',asynchronous:true, onSuccess: s, onFailure: f});
}


/**
 * AJAX GET and update div of ID
 * with the response.
 * 
 * This completely replaces the
 * div contents.
 *
 * Any javascript as part of the
 * response will be executed.
 *
 * @param string url
 * @param int id div id to replace
 */
function ar_g_u(url, id) {
    $('body').style.cursor='progress';
    new Ajax.Updater(id,
                     url,
                     {
                         method:'get',
                         asynchronous:true,
                         evalScripts:true,
                         onCreate: function() {
                               $('body').style.cursor='wait';
                         },
                         onComplete: function() {
                             $('body').style.cursor='default';
                         }
                     });
}

/**
 * AJAX GET and append div of ID
 * with the response.
 *
 * The response text/html/js will be
 * appended to the bottom of the div. 
 *
 * Any javascript as part of the
 * response will be executed.
 *
 * @param string url
 * @param int id div ID to append
 */
function ar_g_a(url, id) {
    var ajax = new Ajax.Updater(
         id,
         url,
            {
                method:'get',
                insertion:Insertion.Bottom,
                evalScripts:true
            }
         );
}

/**
 * AJAX POST and update div of ID
 * with the response.
 * This completely replaces the
 * div contents.
 *
 * Any javascript as part of the
 * response will be executed.
 * 
 * @param Form object
 * @param string id div id to replace
 */
function ar_p_u(formobj,divid) {
    var ser = formobj.attributes['action'].value;
    new Ajax.Updater(
        divid,
        ser,
        {
            method:'post',
            asynchronous:true,
            evalScripts:true,
            parameters:Form.serialize(formobj)
        }
        );
}

/**
 * AJAX POST and append div of ID
 * with the response.
 *
 * The response text/html/js will be
 * appended to the bottom of the div
 *
 * Any javascript as part of the
 * response will be executed.
 * 
 * @param Form object
 * @param string id div id to append
 */
function ar_p_a(formobj,divid) {
    var ser = formobj.attributes['action'].value;
    new Ajax.Updater(
        divid,
        ser,
        {
            method:'post',
            asynchronous:true,
            evalScripts:true,
            insertion:Insertion.Bottom,
            parameters:Form.serialize(formobj)
        }
        );
}

/**
 * AJAX POST and update div of ID
 * with the response.  This is used
 * for the form engine generated
 * form.
 *
 * This completely replaces the
 * div contents.
 *
 * Any javascript as part of the
 * response will be executed.
 * 
 * @param Form object
 * @param string id div id to append
 */
function ar_fp_u(formobj,divid) {
    var ser = formobj.attributes['action'].value;
    new Ajax.Updater(
        divid,
        ser,
        {
            method:'post',
            asynchronous:true,
            evalScripts:true,
            parameters:Form.serialize(formobj)+'&_form_action='+formobj.elements['_form_action'].value
        }
        );
}

/**
 * AJAX POST and append div of ID
 * with the response.  This is used
 * for the form engine generated
 * form.
 *
 * The response text/html/js will be
 * appended to the bottom of the div
 *
 * Any javascript as part of the
 * response will be executed.
 * 
 * @param Form object
 * @param string id div id to append
 */
function ar_fp_a(formobj,divid) {
    var ser = formobj.attributes['action'].value;
    new Ajax.Updater(
        divid,
        ser,
        {
            method:'post',
            asynchronous:true,
            evalScripts:true,
            insertion:Insertion.Bottom,
            parameters:Form.serialize(formobj)+'&_form_action='+formobj.elements['_form_action'].value
        }
        );
}

/**
 * Ajax GET request to a url.
 * Compatibility wrapper for
 * newer ar_g_message(url)
 *
 * @param string url
 */
function g_message(url) {
    ar_g_message(url);
}

/**
 * show notification message for n seconds
 * in a div with id='idMessage'
 *
 * @param XMLHttpRequest
 * @param time_duration 
 */
function message_show(message, time_duration) {
    $('idMessage').innerHTML=message;
    Effect.Appear('idMessage', {queue:'front',duration: 0.1});
    Effect.Fade('idMessage',{queue:'end',duration:time_duration});
}

/**
 * shortcut for the g_message() function
 * This shows a message for 5 seconds.
 *
 * @param XMLHttpRequest 
 */
function m_s(message) {
    message_show(message.responseText, 2);
}

/**
 * shortcut for the error_show() function
 * This shows an error message for 2 seconds.
 *
 * @param XMLHttpRequest
 */
function e_s(message) {
    error_show(message.responseText, 2);
}


/**
 * show 'error' message in a div with
 * id='idMessage'
 *
 * @param XMLHttpRequest
 * @param duration (seconds)
 */
function error_show(message, duration) {
    $('idMessage').innerHTML=message;
    $('idMessage').style.visibility='visible';
    $('idMessage').style.backgroundcolor='red';
    $('idMessage').style.color='white';
    $('idMessage').style.opacity=1;

    if (duration != 0) {
    	setTimeout("Effect.Fade('idMessage');",duration*1000);        
    }
}