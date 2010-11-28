
var validate_has_error = 0;

/**
 * A set of simple js validation
 * functions
 *
 */
function validate_required(id) {
//alert(document.getElementById('formLogin'));
    if (!document.getElementById(id).value) {
        validate_show_error(id, 'This field cannot be empty');
    }
}

/**
 * Shows the error
 *
 */
function validate_show_error(id, str) {
    document.getElementById('error' + id).innerHTML = str;
    document.getElementById('error' + id).style.display = '';
    validate_has_error = 1;
}