/*** AJAX WIDGET PROCESSOR ************************************************************************************/

/**
 * AJAX processor
 *
 * @author Suren Markosian
 *
 * @param string
 * @param string
 * @param string
 * @param int
 */
function AJAX(url, id, method, append) {

    // save the request url
    this._url = url;

    // xml http request object
    this._request = this._getXMLHTTPRequest();

   // POST or GET
   if (typeof method != 'undefined') {
       this._method = method;
   }
   else {
       this._method = 'GET';
   }

    // ID for the dom element for the content
    this._widgetID = id;

    // this is used to fade the current content
    this._fader = null;

    this._append = append;
}

/**
 * Sets URL
 *
 */
AJAX.prototype.setURL = function(url) {
   this._url = url;
}

/**
 * This function will enable
 * content fader
 *
 */
AJAX.prototype.enableFader = function() {
   this._fader = new Fader(document.getElementById(this._widgetID));
}

/**
 * Get request object
 *
 * @return object
 */
AJAX.prototype._getXMLHTTPRequest = function() {
    var req;
    if (window.XMLHttpRequest) {
        try {
            req=new XMLHttpRequest();
        }
        catch(e) {
            req=false;
        }
    }
    else if (window.ActiveXObject) {
        try {
            req=new ActiveXObject('Msxml2.XMLHTTP');
        }
        catch(e) {
            try {
                req=new ActiveXObject('Microsoft.XMLHTTP');
            }
            catch(e) {
                req=false;
            }
        }
    }
    return req;
}

/**
 * send request
 *
 * @param
 */
AJAX.prototype.send = function(message) {

    // change cursor to wait state
    document.getElementById(this._widgetID).style.cursor='wait';

    if (this._fader != null) {
        this._fader.fadeOut();
    }

    // set the var so we can scope the callback
	var _this = this;
    this._request.onreadystatechange = function() {_this._processRequest()};

    this._request.open(this._method, this._url, true);
    if (this._method == 'POST') {
        this._request.setRequestHeader('Content-Type', '"application/x-www-form-urlencoded; charset=UTF-8');
    }
    this._request.send(null);
}

AJAX.prototype.post = function(form) {

    this._url = form.attributes['action'].value;

    for(var i = 0; i < form.length; i++) {
        element = form.elements[i];
        if (!element.disabled) {
            if (element.type == 'checkbox' && !element.checked) {
                continue;
            }
            this._url += '&' + element.name + '=' + element.value;
        }
    }

    this.send();

}

/**
 * Processes the returned request
 * from the server
 *
 */
AJAX.prototype._processRequest = function() {
    if (this._request.readyState==4 && this._request.status==200) {
        var text = this._request.responseText;

        // firefox/opera only
//        var replacement_div = document.getElementById(this._widgetID);
//
//        var node = document.createElement('div');
//        node.innerHTML = text;
//        replacement_div.innerHTML = '';
//        replacement_div.appendChild(node);

        if (this._append) {
            document.getElementById(this._widgetID).innerHTML += text;
        } else {
            document.getElementById(this._widgetID).innerHTML = text;
        }
        
        this._launchJavascript(text);

        // restore the cursor
        document.getElementById(this._widgetID).style.cursor='auto';

        if (this._fader != null) {
            this._fader.show();
        }

    }
}
AJAX.prototype._launchJavascript = function(responseText) {

  // RegExp from prototype.sonio.net
  var ScriptFragment = '(?:<script.*?>)((\n|.)*?)(?:</script>)';

  var match    = new RegExp(ScriptFragment, 'img');
  var scripts  = responseText.match(match);

    if(scripts) {
        var js = '';
        for(var s = 0; s < scripts.length; s++) {
            var match = new RegExp(ScriptFragment, 'im');
            js += scripts[s].match(match)[1];
        }
        eval(js);
    }
}

/**
 * send get request
 *
 */
function q(url, id, append) {
    x = new AJAX(url, id, 'GET', append);
//    x.enableFader();
    x.send();
}

/**
 * send post request
 *
 */
function p(form, id, message) {
    x = new AJAX(null, id, 'POST');
//    x.enableFader();
    x.post(form);
}

/*** Object visibility ******************************************************************/

/**
 * toggle visibility
 * of an element
 */
function toggleDisplay(id) {
    e = document.getElementById(id);

    if (e.style.display == 'none') {
        e.style.display = '';
    }
    else {
        e.style.display = 'none';
    }
}




/*** Fader ******************************************************************/

var fader;

// Fade interval in milliseconds
Fader.INTERVAL = 5;

/**
 * Fader class handles all
 * fade effects
 *
 * @param element - The element to fade
 * @param speed - (optional, default 2) - the speed to fade at, from 0.0 to 100.0
 * @param initialOpacity (optional, default 100) - element's starting opacity, 0 to 100
 * @param minOpacity (optional, default 0) - element's minimum opacity, 0 to 100
 * @param maxOpacity (optional, default 0) - element's minimum opacity, 0 to 100
 *
 * @author Suren Markosian
 */
function Fader(element, rate, initialOpacity, minOpacity, maxOpacity) {
  this._element = element;
  this._intervalID = null;
  this._rate = 2;
  this._isFadeOut = true;

  // Set initial opacity and bounds
  // NB use 99 instead of 100 to avoid flicker at start of fade
  this._minOpacity = 0;
  this._maxOpacity = 99;
  this._opacity = 99;

  if (typeof minOpacity != 'undefined') {
    if (minOpacity < 0) {
      this._minOpacity = 0;
    } else if (minOpacity > 99) {
      this._minOpacity = 99;
    } else {
      this._minOpacity = minOpacity;
    }
  }

  if (typeof maxOpacity != 'undefined') {
    if (maxOpacity < 0) {
      this._maxOpacity = 0;
    } else if (maxOpacity > 99) {
      this._maxOpacity = 99;
    } else {
      this._maxOpacity = maxOpacity;
    }

    if (this._maxOpacity < this._minOpacity) {
      this._maxOpacity = this._minOpacity;
    }
  }

  if (typeof initialOpacity != 'undefined') {
    if (initialOpacity > this._maxOpacity) {
      this._opacity = this._maxOpacity;
    } else if (initialOpacity < this._minOpacity) {
      this._opacity = this._minOpacity;
    } else {
      this._opacity = initialOpacity;
    }
  }

  // See if we're using W3C opacity, MSIE filter, or just
  // toggling visiblity
  if (typeof element.style.opacity != 'undefined') {
    this._updateOpacity = this._updateOpacityW3c;

  }

  else if (typeof element.style.filter != 'undefined') {
    // If there's not an alpha filter on the element already, add one
    if (element.style.filter.indexOf("alpha") == -1) {

      element.style.filter = "alpha(opacity="+this._opacity+")";
    }

    this._updateOpacity = this._updateOpacityMSIE;

  } else {

    this._updateOpacity = this._updateVisibility;
  }

  this._updateOpacity();
}

/**
 * Initiates a fade out
 *
 */
Fader.prototype.fadeOut = function () {
  this._isFadeOut = true;
  this._beginFade();
}

/**
 * Initiates a fade in
 *
 */
Fader.prototype.fadeIn = function () {
  this._isFadeOut = false;
  this._beginFade();
}

/**
 * Makes the element completely opaque
 * stops any fade in progress
 *
 */
Fader.prototype.show = function () {
  this.stopFade();
  this._opacity = this._maxOpacity;
  this._updateOpacity();
}

/**
 * Makes the element completely transparent
 * stops any fade in progress
 *
 */
Fader.prototype.hide = function () {
  this.stopFade();
  this._opacity = 0;
  this._updateOpacity();
}

/**
 * Halts any fade in progress
 *
 */
Fader.prototype.stopFade = function () {
  clearInterval(this._intervalID);
}

/**
 * Resumes a fade where it was halted
 *
 */
Fader.prototype.resumeFade = function () {
  this._beginFade();
}

/*** Private functions ***/

Fader.prototype._beginFade = function () {
  this.stopFade();
  var objref = this;
  this._intervalID = setInterval(function() { objref._tickFade(); }, Fader.INTERVAL);
}

Fader.prototype._tickFade = function () {

  if (this._isFadeOut) {
    this._opacity -= this._rate;
    if (this._opacity < this._minOpacity) {
      this._opacity = this._minOpacity;
      this.stopFade();
    }
  }
  else {
    this._opacity += this._rate;
    if (this._opacity > this._maxOpacity ) {
      this._opacity = this._maxOpacity;
      this.stopFade();
    }
  }

  this._updateOpacity();
}

Fader.prototype._updateVisibility = function () {

  if (this._opacity > 0) {
    this._element.style.visibility = 'visible';
  }
  else {
    this._element.style.visibility = 'hidden';
  }
}

Fader.prototype._updateOpacityW3c = function () {
  this._element.style.opacity = this._opacity/100;
  this._updateVisibility();
}

Fader.prototype._updateOpacityMSIE = function () {
  this._element.filters.alpha.opacity = this._opacity;
  this._updateVisibility();
}

Fader.prototype._updateOpacity = null;


/**
 * show notification message
 *
 */
function message_show(message, duration) {
    document.getElementById('idMessage').innerHTML=message;
    document.getElementById('idMessage').style.visibility='visible';
    document.getElementById('idMessage').style.opacity=1;

    if (duration != 0) {
        setTimeout('message_hide()', duration*1000);
    }
}


/**
 * hide notification message
 *
 */
function message_hide() {

    var element = document.getElementById('idMessage');

    if (element.style.opacity > 0) {
        element.style.opacity -= 0.02;
        window.setTimeout('message_hide()', 5);
    }
    else {
        element.style.visibility='hidden';
        element.innerHTML='';
        element.style.opacity=0;
    }
}



/**************************************************************************************
DHTML MENU */

function Browser() {

    var ua, s, i;

    this.isIE    = false;  // Internet Explorer
    this.isOP    = false;  // Opera
    this.isNS    = false;  // Netscape
    this.version = null;

    ua = navigator.userAgent;

    s = "Opera";
    if ((i = ua.indexOf(s)) >= 0) {
        this.isOP = true;
        this.version = parseFloat(ua.substr(i + s.length));
        return;
    }

    s = "Netscape6/";
    if ((i = ua.indexOf(s)) >= 0) {
        this.isNS = true;
        this.version = parseFloat(ua.substr(i + s.length));
        return;
    }

    // Treat any other "Gecko" browser as Netscape 6.1.

    s = "Gecko";
    if ((i = ua.indexOf(s)) >= 0) {
        this.isNS = true;
        this.version = 6.1;
        return;
    }

    s = "MSIE";
    if ((i = ua.indexOf(s))) {
        this.isIE = true;
        this.version = parseFloat(ua.substr(i + s.length));
        return;
    }
}

var browser = new Browser();

//----------------------------------------------------------------------------
// Code for handling the menu bar and active button.
//----------------------------------------------------------------------------

var activeButton = null;


function buttonClick(event, menuId) {

    var button;

    // Get the target button element.

    if (browser.isIE)
    button = window.event.srcElement;
    else
    button = event.currentTarget;

    // Blur focus from the link to remove that annoying outline.

    button.blur();

    // Associate the named menu to this button if not already done.
    // Additionally, initialize menu display.

    if (button.menu == null) {
        button.menu = document.getElementById(menuId);
        if (button.menu.isInitialized == null)
        menuInit(button.menu);
    }

    // [MODIFIED] Added for activate/deactivate on mouseover.

    // Set mouseout event handler for the button, if not already done.

    if (button.onmouseout == null)
    button.onmouseout = buttonOrMenuMouseout;

    // Exit if this button is the currently active one.

    if (button == activeButton)
    return false;

    // [END MODIFIED]

    // Reset the currently active button, if any.

    if (activeButton != null)
    resetButton(activeButton);

    // Activate this button, unless it was the currently active one.

    if (button != activeButton) {
        depressButton(button);
        activeButton = button;
    }
    else
    activeButton = null;

    return false;
}

function buttonMouseover(event, menuId) {

    var button;

    // [MODIFIED] Added for activate/deactivate on mouseover.

    // Activates this button's menu if no other is currently active.

    if (activeButton == null) {
        buttonClick(event, menuId);
        return;
    }

    // [END MODIFIED]

    // Find the target button element.

    if (browser.isIE)
    button = window.event.srcElement;
    else
    button = event.currentTarget;

    // If any other button menu is active, make this one active instead.

    if (activeButton != null && activeButton != button)
    buttonClick(event, menuId);
}

function depressButton(button) {

    var x, y;

    // Update the button's style class to make it look like it's
    // depressed.

    button.className += " menuButtonActive";

    // [MODIFIED] Added for activate/deactivate on mouseover.

    // Set mouseout event handler for the button, if not already done.

    if (button.onmouseout == null)
    button.onmouseout = buttonOrMenuMouseout;
    if (button.menu.onmouseout == null)
    button.menu.onmouseout = buttonOrMenuMouseout;

    // [END MODIFIED]

    // Position the associated drop down menu under the button and
    // show it.

    x = getPageOffsetLeft(button);
    y = getPageOffsetTop(button) + button.offsetHeight;

    // For IE, adjust position.

    if (browser.isIE) {
        x += button.offsetParent.clientLeft;
        y += button.offsetParent.clientTop;
    }

    button.menu.style.left = x + "px";
    button.menu.style.top  = y + "px";
    button.menu.style.visibility = "visible";

    // For IE; size, position and show the menu's IFRAME as well.

    if (button.menu.iframeEl != null)
    {
        button.menu.iframeEl.style.left = button.menu.style.left;
        button.menu.iframeEl.style.top  = button.menu.style.top;
        button.menu.iframeEl.style.width  = button.menu.offsetWidth + "px";
        button.menu.iframeEl.style.height = button.menu.offsetHeight + "px";
        button.menu.iframeEl.style.display = "";
    }
}

function resetButton(button) {

    // Restore the button's style class.

    removeClassName(button, "menuButtonActive");

    // Hide the button's menu, first closing any sub menus.

    if (button.menu != null) {
        closeSubMenu(button.menu);
        button.menu.style.visibility = "hidden";

        // For IE, hide menu's IFRAME as well.

        if (button.menu.iframeEl != null)
        button.menu.iframeEl.style.display = "none";
    }
}

//----------------------------------------------------------------------------
// Code to handle the menus and sub menus.
//----------------------------------------------------------------------------

function menuMouseover(event) {

    var menu;

    // Find the target menu element.

    if (browser.isIE)
    menu = getContainerWith(window.event.srcElement, "DIV", "menu");
    else
    menu = event.currentTarget;

    // Close any active sub menu.

    if (menu.activeItem != null)
    closeSubMenu(menu);
}

function menuItemMouseover(event, menuId) {

    var item, menu, x, y;

    // Find the target item element and its parent menu element.

    if (browser.isIE)
    item = getContainerWith(window.event.srcElement, "A", "menuItem");
    else
    item = event.currentTarget;
    menu = getContainerWith(item, "DIV", "menu");

    // Close any active sub menu and mark this one as active.

    if (menu.activeItem != null)
    closeSubMenu(menu);
    menu.activeItem = item;

    // Highlight the item element.

    item.className += " menuItemHighlight";

    // Initialize the sub menu, if not already done.

    if (item.subMenu == null) {
        item.subMenu = document.getElementById(menuId);
        if (item.subMenu.isInitialized == null)
        menuInit(item.subMenu);
    }

    // [MODIFIED] Added for activate/deactivate on mouseover.

    // Set mouseout event handler for the sub menu, if not already done.

    if (item.subMenu.onmouseout == null)
    item.subMenu.onmouseout = buttonOrMenuMouseout;

    // [END MODIFIED]

    // Get position for submenu based on the menu item.

    x = getPageOffsetLeft(item) + item.offsetWidth;
    y = getPageOffsetTop(item);

    // Adjust position to fit in view.

    var maxX, maxY;

    if (browser.isIE) {
        maxX = Math.max(document.documentElement.scrollLeft, document.body.scrollLeft) +
        (document.documentElement.clientWidth != 0 ? document.documentElement.clientWidth : document.body.clientWidth);
        maxY = Math.max(document.documentElement.scrollTop, document.body.scrollTop) +
        (document.documentElement.clientHeight != 0 ? document.documentElement.clientHeight : document.body.clientHeight);
    }
    if (browser.isOP) {
        maxX = document.documentElement.scrollLeft + window.innerWidth;
        maxY = document.documentElement.scrollTop  + window.innerHeight;
    }
    if (browser.isNS) {
        maxX = window.scrollX + window.innerWidth;
        maxY = window.scrollY + window.innerHeight;
    }
    maxX -= item.subMenu.offsetWidth;
    maxY -= item.subMenu.offsetHeight;

    if (x > maxX)
    x = Math.max(0, x - item.offsetWidth - item.subMenu.offsetWidth
    + (menu.offsetWidth - item.offsetWidth));
    y = Math.max(0, Math.min(y, maxY));

    // Position and show the sub menu.

    item.subMenu.style.left       = x + "px";
    item.subMenu.style.top        = y + "px";
    item.subMenu.style.visibility = "visible";

    // For IE; size, position and display the menu's IFRAME as well.

    if (item.subMenu.iframeEl != null)
    {
        item.subMenu.iframeEl.style.left    = item.subMenu.style.left;
        item.subMenu.iframeEl.style.top     = item.subMenu.style.top;
        item.subMenu.iframeEl.style.width   = item.subMenu.offsetWidth + "px";
        item.subMenu.iframeEl.style.height  = item.subMenu.offsetHeight + "px";
        item.subMenu.iframeEl.style.display = "";
    }

    // Stop the event from bubbling.

    if (browser.isIE)
    window.event.cancelBubble = true;
    else
    event.stopPropagation();
}

function closeSubMenu(menu) {

    if (menu == null || menu.activeItem == null)
    return;

    // Recursively close any sub menus.

    if (menu.activeItem.subMenu != null) {
        closeSubMenu(menu.activeItem.subMenu);
        menu.activeItem.subMenu.style.visibility = "hidden";

        // For IE, hide the sub menu's IFRAME as well.

        if (menu.activeItem.subMenu.iframeEl != null)
        menu.activeItem.subMenu.iframeEl.style.display = "none";

        menu.activeItem.subMenu = null;
    }

    // Deactivate the active menu item.

    removeClassName(menu.activeItem, "menuItemHighlight");
    menu.activeItem = null;
}

// [MODIFIED] Added for activate/deactivate on mouseover. Handler for mouseout
// event on buttons and menus.

function buttonOrMenuMouseout(event) {

    var el;

    // If there is no active button, exit.

    if (activeButton == null)
    return;

    // Find the element the mouse is moving to.

    if (browser.isIE)
    el = window.event.toElement;
    else if (event.relatedTarget != null)
    el = (event.relatedTarget.tagName ? event.relatedTarget : event.relatedTarget.parentNode);

    // If the element is not part of a menu, reset the active button.

    if (getContainerWith(el, "DIV", "menu") == null) {
        resetButton(activeButton);
        activeButton = null;
    }
}

// [END MODIFIED]

//----------------------------------------------------------------------------
// Code to initialize menus.
//----------------------------------------------------------------------------

function menuInit(menu) {

    var itemList, spanList;
    var textEl, arrowEl;
    var itemWidth;
    var w, dw;
    var i, j;

    // For IE, replace arrow characters.

    if (browser.isIE) {
        menu.style.lineHeight = "2.5ex";
        spanList = menu.getElementsByTagName("SPAN");
        for (i = 0; i < spanList.length; i++)
        if (hasClassName(spanList[i], "menuItemArrow")) {
            spanList[i].style.fontFamily = "Webdings";
            spanList[i].firstChild.nodeValue = "4";
        }
    }

    // Find the width of a menu item.

    itemList = menu.getElementsByTagName("A");
    if (itemList.length > 0)
    itemWidth = itemList[0].offsetWidth;
    else
    return;

    // For items with arrows, add padding to item text to make the
    // arrows flush right.

    for (i = 0; i < itemList.length; i++) {
        spanList = itemList[i].getElementsByTagName("SPAN");
        textEl  = null;
        arrowEl = null;
        for (j = 0; j < spanList.length; j++) {
            if (hasClassName(spanList[j], "menuItemText"))
            textEl = spanList[j];
            if (hasClassName(spanList[j], "menuItemArrow"))
            arrowEl = spanList[j];
        }
        if (textEl != null && arrowEl != null) {
            textEl.style.paddingRight = (itemWidth
            - (textEl.offsetWidth + arrowEl.offsetWidth)) + "px";
            // For Opera, remove the negative right margin to fix a display bug.
            if (browser.isOP)
            arrowEl.style.marginRight = "0px";
        }
    }

    // Fix IE hover problem by setting an explicit width on first item of
    // the menu.

    if (browser.isIE) {
        w = itemList[0].offsetWidth;
        itemList[0].style.width = w + "px";
        dw = itemList[0].offsetWidth - w;
        w -= dw;
        itemList[0].style.width = w + "px";
    }

    // Fix the IE display problem (SELECT elements and other windowed controls
    // overlaying the menu) by adding an IFRAME under the menu.

    if (browser.isIE) {
        var iframeEl = document.createElement("IFRAME");
        iframeEl.frameBorder = 0;
        iframeEl.src = "javascript:;";
        iframeEl.style.display = "none";
        iframeEl.style.position = "absolute";
        iframeEl.style.filter = "progid:DXImageTransform.Microsoft.Alpha(style=0,opacity=0)";
        menu.iframeEl = menu.parentNode.insertBefore(iframeEl, menu);
    }

    // Mark menu as initialized.

    menu.isInitialized = true;
}

//----------------------------------------------------------------------------
// General utility functions.
//----------------------------------------------------------------------------

function getContainerWith(node, tagName, className) {

    // Starting with the given node, find the nearest containing element
    // with the specified tag name and style class.

    while (node != null) {
        if (node.tagName != null && node.tagName == tagName &&
        hasClassName(node, className))
        return node;
        node = node.parentNode;
    }

    return node;
}

function hasClassName(el, name) {

    var i, list;

    // Return true if the given element currently has the given class
    // name.

    list = el.className.split(" ");
    for (i = 0; i < list.length; i++)
    if (list[i] == name)
    return true;

    return false;
}

function removeClassName(el, name) {

    var i, curList, newList;

    if (el.className == null)
    return;

    // Remove the given class name from the element's className property.

    newList = new Array();
    curList = el.className.split(" ");
    for (i = 0; i < curList.length; i++)
    if (curList[i] != name)
    newList.push(curList[i]);
    el.className = newList.join(" ");
}

function getPageOffsetLeft(el) {

    var x;

    // Return the x coordinate of an element relative to the page.

    x = el.offsetLeft;
    if (el.offsetParent != null)
    x += getPageOffsetLeft(el.offsetParent);

    return x;
}

function getPageOffsetTop(el) {

    var y;

    // Return the x coordinate of an element relative to the page.

    y = el.offsetTop;
    if (el.offsetParent != null)
    y += getPageOffsetTop(el.offsetParent);

    return y;
}
