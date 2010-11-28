if (prefix==null || prefix!='') {
    var prefix = "/images/widgets/";
}

var tree_open = new Image();
tree_open.src = prefix + 'tree_open.gif';

var tree_closed = new Image();
tree_closed.src = prefix + 'tree_closed.gif';

/**
 * This function toggles display property
 * of an html element
 *
 */
function toggle_tree(id) {
    element = $(id);
    img = $('i'+id);
    if (!element) return;

    //Effect.toggle(id, 'Appear', {duration: 0.3});
    if (img.src.charAt(img.src.length-5) == 'n') {
        Effect.SlideUp(id, {duration: 0.2});
        img.src = tree_closed.src;
    } else {
        Effect.SlideDown(id, {duration: 0.2});
        img.src = tree_open.src;
    }

    //$('l'+id).blur();
}

/**
 * Expands a tree branch
 * @param start_id
 */
function expand_b(start_id) {
    i = start_id;
    while (1) {

        element = $(i);
        img = $('i'+ i);
        if (!element) break;
        
        element.className = 'div_tree'
        img.src = tree_open.src;

        i++;
    }
}

/**
 * Collapses a tree branch
 * @param start_id
 */
function collapse_b(start_id) {
    i = start_id;
    while (1) {

        element = $(i);
        img = $('i'+ i);
        if (!element) break;

        element.className = 'div_tree_closed'
        img.src = tree_closed.src;

        i++;
    }
}
