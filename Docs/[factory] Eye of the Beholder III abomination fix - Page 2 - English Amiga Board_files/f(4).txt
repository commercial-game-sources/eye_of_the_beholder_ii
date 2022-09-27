/**
 * @fileoverview Provides common functionality for HTML5 layouts.
 */


/**
 * Image aspect ratios.
 * @enum {number}
 */
var AspectRatio = {
  MAX: 4,
  MIN: .25
};


/**
 * Dom attributes to add to elements.
 * @enum {string}
 */
var DomAttribute = {
  TITLE: 'title'
};


/**
 * Parts of the user agent value, which are used to detect IE.
 * @enum {string}
 */
var ieUserAgentPart = {
  IE_V11_AND_ABOVE: 'trident/',
  IE_BELOW_V11: 'msie'
};


/**
 * Layouts heights in pixels.
 * @enum {number}
 */
var LayoutHeight = {
  AD_320x100: 100,
  AD_320x50: 50,
  AD_468x60: 60,
  HORIZONTALS: 90,
  VERTICALS: 600
};


/**
 * Layouts shape types.
 * @enum {string}
 */
var LayoutTypes = {
  HORIZONTAL: 'horizontal',
  MIN: 'minimal',
  SQUARE: 'square',
  VERTICAL: 'vertical'
};


/**
 * Logo coefficient if the aspect ratio is larger than {@code AspectRatio.MAX} &
 * less than {@code AspectRatio.MIN}.
 * @type {number}
 */
var LOGO_COEFFICIENT = 3;


/**
 * Minimum and maximum logo padding in pixels.
 * @enum {number}
 */
var LogoPadding = {
  MAX: 20,
  MIN: 0
};


/**
 * Minimum font size that can be set to the text. Units are pixels.
 * @type {number}
 */
var MIN_FONT_SIZE = 7;


/**
 * Minimum pixel size of the logo. Units are pixels.
 * @type {number}
 */
var MIN_LOGO_SIZE = 20;


/**
 * Representation for the max value the sale discount limit.
 * @private {number}
 */
var MAX_SALE_DISCOUNT_VALUE_ = 100;


/**
 * Suffix for the sale discount.
 * @private {string}
 */
var PERCENT_SYMBOL_ = '%';


/**
 * Star rating constants.
 * @enum {number}
 */
var StarRating = {
  /** Maximum rating delta to show a half of a star. */
  MAX_HALF_STAR_DELTA: .71,
  /** Maximum star rating number to show. */
  MAX_STARS_TO_SHOW: 5,
  /** Minimum rating delta to show a half of a star. */
  MIN_HALF_STAR_DELTA: .29,
  /** Minimum star rating to show stars. */
  MIN_STARS_TO_SHOW: 3
};


/**
 * Regular expressions to parse HEX color.
 * @enum {RegExp}
 */
var RgbChannelsRegExps = {
  /** Returns hex representation of every channel of the color. */
  FULL: /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i,
  /** Returns symbols that represent channels. */
  SHORT: /^#?([a-f\d])([a-f\d])([a-f\d])$/i
};


/**
 * Utils object with common functionality for the layouts.
 * @return {!Object.<function>} Globally available functions.
 */
var helpers = (function() {
  /**
   * Shorthand for style utils.
   * @type {!Object}
   */
  var styleUtils = ddab.layouts.utils.styleUtils;

  var utilsModule = angular.module('utils');


  /**
   * Controller for using data binding in layout.
   * @param {Object} $scope AngularJS layout $scope.
   * @param {Object} dynamicData Dynamic data from DAB.
   */
  function LayoutController($scope, dynamicData) {
    $scope.data = dynamicData.google_template_data.adData[0];
    $scope.frameHeight = dynamicData.google_height;
    $scope.fieldReference = '';

    $scope.products = utils.parse($scope.data, 'Product').slice(0);
    $scope.headline = utils.parse($scope.data, 'Headline')[0];
    $scope.design = utils.parse($scope.data, 'Design')[0];

    if ($scope.design.priceSize < MIN_FONT_SIZE) {
      $scope.design.priceSize = MIN_FONT_SIZE;
    }
    if ($scope.design.nameSize < MIN_FONT_SIZE) {
      $scope.design.nameSize = MIN_FONT_SIZE;
    }
    if ($scope.design.headlineSize < MIN_FONT_SIZE) {
      $scope.design.headlineSize = MIN_FONT_SIZE;
    }
    if ($scope.design.descriptionSize < MIN_FONT_SIZE) {
      $scope.design.descriptionSize = MIN_FONT_SIZE;
    }

    switch (parseInt($scope.frameHeight, 10)) {
      case LayoutHeight.VERTICALS:
        $scope.layoutType = LayoutTypes.VERTICAL;
        break;
      case LayoutHeight.AD_468x60:
      case LayoutHeight.HORIZONTALS:
        $scope.layoutType = LayoutTypes.HORIZONTAL;
        break;
      case LayoutHeight.AD_320x100:
      case LayoutHeight.AD_320x50:
        $scope.layoutType = LayoutTypes.MIN;
        break;
      default:
        $scope.layoutType = LayoutTypes.SQUARE;
    }


    /**
     * Checks whether the given image has already been loaded.
     * @param {string} url Image source URL.
     * @return {boolean} Whether the given URL is in preloaded images list.
     */
    $scope.checkUrl = function(url) {
      if (!url || url == 'empty') {
        return false;
      }
      return utils.isLoadedRes(url);
    };


    /**
     * Verifies if the star rating should be shown.
     * @param {string} rating Rating value.
     * @return {boolean} If the star rating should be shown.
     */
    $scope.isRatingValid = function(rating) {
      return $scope.isTrulyNumber(rating) &&
          parseFloat(rating) >= StarRating.MIN_STARS_TO_SHOW;
    };


    /**
     * Verifies whether the rating should have half stars. According to Google
     * Rating all the ratings with remainders between .29 and .71 should show
     * half stars.
     * @param {string=} opt_rating Star rating as a string.
     * @return {boolean} If the star rating is between .29 and .71, and should
     * show half of a star.
     */
    $scope.isShownHalf = function(opt_rating) {
      opt_rating = opt_rating || 0;
      var floor = Math.floor(parseFloat(opt_rating));

      // Don't show half star for rating more than
      // {@code StarRating.MAX_STARS_TO_SHOW} or equals.
      if (floor >= StarRating.MAX_STARS_TO_SHOW) {
        return false;
      }
      var mod = opt_rating % floor;
      return mod > StarRating.MIN_HALF_STAR_DELTA ?
          mod < StarRating.MAX_HALF_STAR_DELTA : false;
    };


    /**
     * Builds array of the star for the rating.
     * @param {number} rating Rating value.
     * @return {Array.<number>} Array of the rating stars.
     */
    $scope.starRatingArray = function(rating) {
      if ($scope.isRatingValid(rating)) {
        var floorRating = parseFloat(rating);
        if (floorRating > StarRating.MAX_STARS_TO_SHOW) {
          rating = StarRating.MAX_STARS_TO_SHOW;
        }
      } else {
        rating = 0;
      }

      return new Array(ratingToInteger(rating));
    };


    /**
     * Verifies if the passed parameter maybe converted to number.
     * @param {string} numString The string to verify.
     * @return {boolean} Returns true if the string can be converted to number.
     */
    $scope.isTrulyNumber = function(numString) {
      return !!Number(numString);
    };


    /**
     * Verifies if the string from DAB is really empty.
     * @param {string} str String to verify.
     * @return {boolean} Returns true if the string is empty.
     */
    $scope.isEmpty = function(str) {
      if (!str) {
        return true;
      }
      str = str.trim();
      return !str || !str.length;
    };


    /**
     * Converts string from DAB to boolean. DAB provides true or false in
     * uppercase.
     * @param {string} str String to convert.
     * @return {boolean} Boolean representation of the string provided.
     */
    $scope.toBoolean = function(str) {
      if (!str) {
        return false;
      }
      return str.toLowerCase() === 'true';
    };


    // Normalize discount field for each product.
    angular.forEach($scope.products, function(product) {
      if (!$scope.isEmpty(product.salePercentDiscount)) {
        var discount =
            Math.abs(Math.round(product.salePercentDiscount * 100));
        if (discount == 0) {
          product.salePercentDiscount = '';
        } else {
          if (discount > MAX_SALE_DISCOUNT_VALUE_) {
            discount = MAX_SALE_DISCOUNT_VALUE_;
          }
          product.salePercentDiscount = (discount * -1) + PERCENT_SYMBOL_;
        }
      }
    });

    var prodClickOnly = $scope.toBoolean($scope.headline.productClickOnly);

    if ($scope.products.length && $scope.products[0].url) {
      $scope.fieldReference = prodClickOnly ? 'Product_0_url' : '';
      $scope.currentProductIndex = 0;
    }

    $scope.$on('urlchange', function(e, index) {
      var currentIndex = parseInt(index, 10);
      $scope.$apply(function() {
        $scope.fieldReference = !isNaN(currentIndex) ?
            'Product_' + currentIndex + '_url' : '';

        if (!isNaN(currentIndex)) {
          $scope.currentProductIndex = currentIndex;
        }
      });
    });

    /**
     * Builds lists of the products to be used in the carousels.
     * @param {number} maxItems Maximum number of items in the list.
     * @param {number} maxLists Maximum number of lists.
     * @return {Array.<Object>} All the products lists available.
     */
    $scope.buildProductLists = function(maxItems, maxLists) {
      var res = [];
      var products = $scope.products;
      var chunk = maxItems || 4;
      var max = maxLists || 10;
      for (var i = 0, j = 0; i < products.length && j++ < max; i += chunk) {
        var list = products.slice(i, i + chunk);
        list = list.concat(products.slice(0, chunk - list.length));
        res.push(list);
      }
      return res;
    };


    /**
     * Shades given color.
     * @param {string} color Color to shade.
     * @param {number} percent Percentage to shade.
     * @return {string} Updated color.
     */
    $scope.shadeColor = function(color, percent) {
      var f = parseInt(color.slice(1), 16),
          t = percent < 0 ? 0 : 255,
          p = percent < 0 ? percent * -1 : percent,
          R = f >> 16,
          G = f >> 8 & 0x00FF,
          B = f & 0x0000FF;

      return '#' +
          (0x1000000 + (Math.round((t - R) * p) + R) *
          0x10000 + (Math.round((t - G) * p) + G) *
          0x100 + (Math.round((t - B) * p) + B)).toString(16).slice(1);
    };


    /**
     * Changes the brightness of the color using its RGBA representation.
     * @param {string} color The color to change.
     * @param {number} delta Percentage to change the brightness of the color.
     * @param {number=} opt_alpha Alpha channel of the color.
     * @return {?string} Updated color in RGBA.
     */
    $scope.changeBrightnessRGBA = function(color, delta, opt_alpha) {
      var alpha = opt_alpha || 0;
      var hex = getFullHexColor(color.toColor());
      var result = RgbChannelsRegExps.FULL.exec(hex);
      var rgb = '', part;
      for (var i = 1; i < result.length; i++) {
        part = parseInt(result[i], 16);
        part += part * delta;
        rgb += Math.round(Math.min(Math.max(0, part), 255)) + ',';
      }

      return rgb ? 'rgba(' + rgb + alpha + ')' : null;
    };
  }


  /**
   * Sets last product the user had interaction with. By default, the user exits
   * to product with index 0 if the {@code prodClickOnly} is set to true, and to
   * destination URL if the {@code prodClickOnly} is set to false.
   * @return {!angular.Directive} Directive definition object.
   */
  utilsModule.directive('interaction', function() {
    return {
      restrict: 'A',
      link: function(scope, el, attrs) {
        var prodClickOnly = scope.toBoolean(scope.headline.productClickOnly);

        el.bind('mouseover', function() {
          scope.$emit(attrs.interaction, attrs.productIndex);
        });

        if (!prodClickOnly) {
          el.bind('mouseleave', function() {
            scope.$emit(attrs.interaction, '');
          });
        }
      }
    };
  });


  /**
   * Exposes observedImageFit as a custom attribute to set watcher
   * for layouts with image pre-loading and carousel.
   * @return {!angular.Directive} Directive definition object.
   */
  utilsModule.directive('observedImageFit', function() {
    return {
      restrict: 'A',
      link: function(scope, el, attr) {
        var srcLoc = attr.loc;
        var done = false;
        scope.$watch(srcLoc, function() {
          if (!done) {
            var src = scope.$eval(srcLoc);
            if (scope.checkUrl(src)) {
              new ddab.layouts.utils.DynamicImageFit(el[0], src, attr.scaletype,
                  attr.aligntype);
            }
            done = true;
          }
        });
      }
    };
  });


  /**
   * Exposes extTextFit as a custom attribute to prevent
   * anchor exit for the carousels.
   * @param {!angular.$timeout} $timeout The Angular timeout service.
   * @return {!angular.Directive} Directive definition object.
   */
  utilsModule.directive('extTextFit', function($timeout) {
    return {
      restrict: 'A',
      link: function(scope, el) {
        $timeout(function() {
          extTextFit(el);
        });
      }
    };
  });


  /**
   * Exposes dynamicStyles as a custom attribute. Handles the dynamic styles and
   * adds them to the document. Workaround for angular not binding data for
   * style tag.
   * @param {!angular.$timeout} $timeout The Angular timeout service.
   * @return {!angular.Directive} Directive definition object.
   */
  utilsModule.directive('dynamicStyle', ['$timeout', function($timeout) {
    return {
      restrict: 'A',
      link: function(scope, element) {
        // TODO: Find more optimized solution. Any change here causes endless
        // loop for the layouts.
        $timeout(function() {
          var el = element[0];
          var styleEl = document.createElement('style');
          styleEl.innerHTML = el.textContent;
          document.getElementsByTagName('head')[0].appendChild(styleEl);
          el.innerHTML = '';
        });
      }
    };
  }]);


  /**
   * Exposes logoFit as a custom attribute. Handles logo, if available. Adds
   * padding to the logo.
   * @return {!angular.Directive} Directive definition object.
   */
  utilsModule.directive('logoFit', function() {
    return {
      restrict: 'A',
      link: function(scope, element, attrs) {
        scope.$watch(attrs.loc, function() {
          var el = element[0];
          var src = scope.$eval(attrs.loc);

          if (scope.checkUrl(src)) {
            var padding = parseInt(scope.design.logoPadding, 10);
            padding = !isNaN(padding) ? padding : 0;
            padding = Math.min(Math.max(LogoPadding.MIN, padding),
                LogoPadding.MAX);
            var logoMargins = utils.logoMargin(element);
            var parent = element.parent();

            utils.preload(src, function(image) {
              var imgRatio = image.width / image.height;
              var minLogoSize = imgRatio > AspectRatio.MAX ||
                  imgRatio < AspectRatio.MIN ?
                  MIN_LOGO_SIZE * LOGO_COEFFICIENT : MIN_LOGO_SIZE;

              // Available space is divided by 2 to add equal value to the both
              // sides.
              var availableHeight = parseInt((parent[0].offsetHeight -
                  minLogoSize) / 2, 10);
              var availableWidth = parseInt((parent[0].offsetWidth -
                  minLogoSize) / 2, 10);
              parent.css({
                'padding-bottom': Math.min(availableHeight, padding +
                    logoMargins.b) + 'px',
                'padding-left': Math.min(availableWidth, padding +
                    logoMargins.l) + 'px',
                'padding-right': Math.min(availableWidth, padding +
                    logoMargins.r) + 'px',
                'padding-top': Math.min(availableHeight, padding +
                    logoMargins.t) + 'px'
              });
              element.addClass('inline-wrapper');
              new ddab.layouts.utils.DynamicImageFit(el, src, attrs.scaletype,
                  attrs.aligntype);
            });
          }
        });
      }
    };
  });


  /**
   * Exposes flexFit as a custom attribute.
   * @return {!angular.Directive} Directive definition object.
   */
  utilsModule.directive('flexFit', function() {
    return {
      restrict: 'A',
      link: function(scope, el) {
        scope.$evalAsync(function() {
          flex(el);
        });
      }
    };
  });


  /**
   * Increases the size of the child blocks by the space available
   * in the parent.
   * @param {!angular.JQLite} el The jQuery element object to handle.
   */
  function flex(el) {
    var space = calculateAvailableSpace(el[0]);
    var availableWidth = space.width;
    var availableHeight = space.height;
    var children = el.children();
    var partsCount = 0;
    var flexCoef = 0;
    var currentElement;

    // Calculate the number of parts of the available free space to use.
    angular.forEach(children, function(element) {
      if (getStyleProperty(element, 'display') != 'none') {
        var outer = calculateOuterIndent(element);
        flexCoef = getFlexCoefficient(angular.element(element));
        availableWidth -= getNumericProperty(element, 'width') + outer.x;
        availableHeight -= getNumericProperty(element, 'height') + outer.y;
        partsCount += flexCoef;
      }
    });

    availableWidth = availableWidth < 0 ? 0 : availableWidth;
    availableHeight = availableHeight < 0 ? 0 : availableHeight;

    // Defined the minimum width or height of this single part.
    var widthPart = parseInt(availableWidth / partsCount, 10);
    widthPart = !isNaN(widthPart) ? widthPart : 0;
    var heightPart = parseInt(availableHeight / partsCount, 10);
    heightPart = !isNaN(heightPart) ? heightPart : 0;

    // Calculate and add the space to child element width or height to
    // extend it.
    angular.forEach(children, function(element) {
      var elementWidth = getNumericProperty(element, 'width');
      var widthToSet = elementWidth > space.width ?
          space.width : elementWidth;
      var elementHeight = getNumericProperty(element, 'height');
      var heightToSet = elementHeight > space.height ?
          space.height : elementHeight;

      currentElement = angular.element(element);

      // Reduce element sizes if it is larger than the parent element.
      if (getStyleProperty(element, 'display') != 'none') {
        flexCoef = getFlexCoefficient(currentElement);
        currentElement.css({
          width: '{0}px'.format(widthToSet + Math.floor(flexCoef * widthPart)),
          height: '{0}px'.format(heightToSet +
              Math.floor(flexCoef * heightPart))
        });

        flex(currentElement);
      }
    });
  }


  /**
   * Increases the size of the child blocks by the space available
   * in the parent.
   * @param {!angular.JQLite} el The jQuery element object to handle.
   */
  function calculateAvailableSpace(el) {
    var indent = calculateIndent(el);
    return {
      width: getNumericProperty(el, 'width') - indent.x,
      height: getNumericProperty(el, 'height') - indent.y
    };
  }


  /**
   * Calculates useful size of the element.
   * @param {Element} el The DOM element to get the size.
   * @return {!Object.<number>} Object with element size.
   */
  function calculateIndent(el) {
    var paddingBorderBox = styleUtils.getPaddingBorderBox(el);

    // Floor is used to avoid unintended increasing of the size, because some
    // browsers add fractional part to the correct size if the page is zoomed.
    return {
      x: Math.floor(paddingBorderBox.left) + Math.floor(paddingBorderBox.right),
      y: Math.floor(paddingBorderBox.top) + Math.floor(paddingBorderBox.bottom)
    };
  }


  /**
   * Calculates horizontal and vertical indents for the element.
   * Includes margins.
   * @param {Element} el The DOM element to get the indent.
   * @return {!Object.<number>} Object with horizontal and vertical indents.
   */
  function calculateOuterIndent(el) {
    var margins = styleUtils.getMarginBox(el);
    return {
      x: margins.left + margins.right,
      y: margins.top + margins.bottom
    };
  }


  /**
   * Gets requested numeric CSS property value from the element.
   * @param {Element} el The DOM element to get the indent.
   * @param {string} name Property name.
   * @return {number} Property value in pixels.
   */
  function getNumericProperty(el, name) {
    var style = window.getComputedStyle(el, null);
    var value;
    var rect = el.getBoundingClientRect();

    if (style) {
      if (name == 'height') {
        value = rect.bottom - rect.top;
      } else if (name == 'width') {
        value = rect.right - rect.left;
      } else {
        value = style[name];
      }
      return !isNaN(value) ? Math.round(value) : 0;
    } else {
      return 0;
    }
  }


  /**
   * Gets requested CSS property value from the element.
   * @param {Element} el The DOM element to get the indent.
   * @param {string} name Property name.
   * @return {string} Property value.
   */
  function getStyleProperty(el, name) {
    var style = window.getComputedStyle(el, null);

    if (style) {
      return style[name] ? style[name] : '';
    } else {
      return '';
    }
  }


  /**
   * Retrieves the flex level from the attribute and converts it to a number.
   * Used in the {@code flex} method.
   * @param {!angular.JQLite} el The jQuery element object to handle.
   * @return {number} Flex level.
   */
  function getFlexCoefficient(el) {
    var flexNum = el.attr('flex') || 0;
    return parseInt(flexNum, 10);
  }


  /**
   * Creates a shallow object clone.
   * @param {Object} obj Object to be cloned.
   * @return {!Object} Returns cloned object.
   */
  function clone(obj) {
    var res = {};
    for (var prop in obj) {
      if (obj.hasOwnProperty(prop)) {
        res[prop] = obj[prop];
      }
    }
    return res;
  }


  /**
   * Creates DynamicTextFit and applies alignText on it
   * @param {!angular.Object} element Object of the DOM element to handle.
   */
  function extTextFit(element) {
    var minfontsize = element.attr('minfontsize');
    var multiline = element.attr('multiline');
    var truncate = element.attr('truncate');
    var originalText = element.text().trim();

    var dynamicTextFit = new ddab.layouts.utils.DynamicTextFit(element[0],
        minfontsize && minfontsize.toNumber(),
        multiline && multiline.toBoolean(),
        truncate && truncate.toBoolean());

    dynamicTextFit.addEventListener('textfit', function() {
      var scaledFontSize = dynamicTextFit.getScaledFontSize();
      var isTruncated = dynamicTextFit.isTruncated();

      // If the text is truncated then add "title" attribute to the original
      // element.
      if (isTruncated && !element[0].hasAttribute(DomAttribute.TITLE)) {
        element[0].setAttribute(DomAttribute.TITLE, originalText);
      }

      alignText(element, scaledFontSize);
    });

    dynamicTextFit.scaleText();
  }


  /**
   * Aligns text in the element.
   * @param {!angular.JQLite} element The jQuery element object to handle.
   * @param {number} scaledFontSize The text font size after text fit.
   */
  function alignText(element, scaledFontSize) {
    var valign = element.attr('valign');
    var text = wrapText(element, scaledFontSize);

    if (valign) {
      element.addClass('inline-wrapper');
      text.css({
        'display': 'inline-block',
        'height': 'auto',
        'vertical-align': valign,
        'width': '100%'
      });
    }
  }


  /**
   * Wraps text into DOM element to apply vertical alignment.
   * @param {!angular.JQLite} element The jQuery element object to handle.
   * @param {number} scaledFontSize The text font size after text fit.
   * @return {!Element} Returns text wrapped into newly created DOM element.
   */
  function wrapText(element, scaledFontSize) {
    var text = element.text();
    var tagElement = document.createElement('span');
    var ellipsis = window.getComputedStyle(element[0])
        .getPropertyValue('text-overflow');

    /**
     * @type {Array.<angular.JQLite>}
     */
    var tag = angular.element(tagElement);
    tag.text(text).css({
      'font-size': scaledFontSize + 'px'
    });

    if (element.attr('truncate').toBoolean()) {
      tag.css({
        'overflow': 'inherit',
        'text-overflow': ellipsis || 'clip',
        'white-space': 'inherit'
      });
    }

    element.html('').append(tag);
    return tag;
  }


  /**
   * Converts star rating string to an integer, following Google Rating
   * integer-to-star value rules. All the ratings that have remainders larger
   * than .71 are converted to the next integer (eg. 3.5 to 3, and 3.8 to 4).
   * @param {string=} opt_rating Star rating as a string.
   * @return {number} Star rating as an integer number.
   */
  function ratingToInteger(opt_rating) {
    opt_rating = opt_rating || 0;
    var floor = Math.floor(parseFloat(opt_rating));
    var remainder = opt_rating % floor >= StarRating.MAX_HALF_STAR_DELTA ?
        1 : 0;
    return floor + remainder;
  }


  /**
   * Expands shorthand form (e.g. "03F") to full form (e.g. "0033FF").
   * @param {string} hex Color in hexidecimal.
   * @return {string} color in full hexidecimal.
   */
  function getFullHexColor(hex) {
    return hex.replace(RgbChannelsRegExps.SHORT, function(r, g, b) {
      return r + r + g + g + b + b;
    });
  }


  /**
   * Check if the user is using IE.
   * @return {boolean} Whether is IE.
   */
  function isIE() {
    var myNav = navigator.userAgent.toLowerCase();
    return ((myNav.indexOf(ieUserAgentPart.IE_BELOW_V11) != -1) ||
        myNav.indexOf(ieUserAgentPart.IE_V11_AND_ABOVE) != -1);
  }

  return {
    alignText: alignText,
    clone: clone,
    extTextFit: extTextFit,
    flex: flex,
    getNumericProperty: getNumericProperty,
    getStyleProperty: getStyleProperty,
    isIE: isIE,
    LayoutController: LayoutController,
    wrapText: wrapText
  };
})();
