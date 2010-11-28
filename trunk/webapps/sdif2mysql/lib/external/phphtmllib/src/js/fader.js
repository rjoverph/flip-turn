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
