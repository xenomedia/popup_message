(function ($) {
  Drupal.behaviors.popup_message_popup = {
    attach: function(context, settings) {
      $('body').not('.sliding-popup-processed').addClass('sliding-popup-processed').each(function() {
        try {
          var enabled = Drupal.settings.popup_message.popup_enabled;
          if(!enabled) {
            return;
          }
          if (!Drupal.popup_message.cookiesEnabled()) {
            return;
          } 
          var status = Drupal.popup_message.getCurrentStatus();
          var clicking_confirms = Drupal.settings.popup_message.popup_clicking_confirmation;
          var agreed_enabled = Drupal.settings.popup_message.popup_agreed_enabled;
          var popup_hide_agreed = Drupal.settings.popup_message.popup_hide_agreed;
          if (status == 0) {
            var next_status = 1;
            if (clicking_confirms) {
              $('a, input[type=submit]').bind('click.popup_message', function(){
                if(!agreed_enabled) {
                  Drupal.popup_message.setStatus(1);
                  next_status = 2;
                }
                Drupal.popup_message.changeStatus(next_status);
              });
            }

            $('.agree-button').click(function(){
              if(!agreed_enabled) {
                Drupal.popup_message.setStatus(1);
                next_status = 2;
              }
              Drupal.popup_message.changeStatus(next_status);
            });

            Drupal.popup_message.createPopup(Drupal.settings.popup_message.popup_html_info);
          } else if(status == 1) {
            Drupal.popup_message.createPopup(Drupal.settings.popup_message.popup_html_agreed);
            if (popup_hide_agreed) {
              $('a, input[type=submit]').bind('click.popup_message_hideagreed', function(){
                Drupal.popup_message.changeStatus(2);
              });
            }

          } else {
            return;
          }
        }
        catch(e) {
          return;
        }
      });
    }
  }

  Drupal.popup_message = {};

  Drupal.popup_message.createPopup = function(html) {
    var popup = $(html)
      .attr({"id": "sliding-popup"})
      .height(Drupal.settings.popup_message.popup_height)
      //.width(Drupal.settings.popup_message.popup_width)
      .hide();
    if(Drupal.settings.popup_message.popup_position) {
      popup.prependTo("body");
      var height = popup.height();
      popup.show()
        .attr({"class": "sliding-popup-top"})
        .css({"top": -1 * height})
        .animate({top: 0}, Drupal.settings.popup_message.popup_delay);
    } else {
      popup.appendTo("body");
      height = popup.height();
      popup.show()
        .attr({"class": "sliding-popup-bottom"})
        .css({"bottom": -1 * height})
        .animate({bottom: 0}, Drupal.settings.popup_message.popup_delay)
    }
    Drupal.popup_message.attachEvents();
  }

  Drupal.popup_message.attachEvents = function() {
	var clicking_confirms = Drupal.settings.popup_message.popup_clicking_confirmation;
    var agreed_enabled = Drupal.settings.popup_message.popup_agreed_enabled;
    $('.find-more-button').click(function(){
      if (Drupal.settings.popup_message.popup_link_new_window) {
        window.open(Drupal.settings.popup_message.popup_link);
      }
      else{
        window.location.href = Drupal.settings.popup_message.popup_link;
      }
    });
    $('.agree-button').click(function(){
      var next_status = 1;
      if(!agreed_enabled) {
        Drupal.popup_message.setStatus(1);
        next_status = 2;
      }
      if (clicking_confirms) {
        $('a, input[type=submit]').unbind('click.popup_message');
      }
      Drupal.popup_message.changeStatus(next_status);
    });
    $('.hide-popup-button').click(function(){
      Drupal.popup_message.changeStatus(2);
    });
  }

  Drupal.popup_message.getCurrentStatus = function() {
	name = 'cookie-agreed';
	value = Drupal.popup_message.getCookie(name);
	return value;
  }

  Drupal.popup_message.changeStatus = function(value) {
    var status = Drupal.popup_message.getCurrentStatus();
    if (status == value) return;
    if(Drupal.settings.popup_message.popup_position) {
      $(".sliding-popup-top").animate({top: $("#sliding-popup").height() * -1}, Drupal.settings.popup_message.popup_delay, function () {
        if(status == 0) {
          $("#sliding-popup").html(Drupal.settings.popup_message.popup_html_agreed).animate({top: 0}, Drupal.settings.popup_message.popup_delay);
          Drupal.popup_message.attachEvents();
        }
        if(status == 1) {
          $("#sliding-popup").remove();
        }
      })
    } else {
      $(".sliding-popup-bottom").animate({bottom: $("#sliding-popup").height() * -1}, Drupal.settings.popup_message.popup_delay, function () {
        if(status == 0) {
          $("#sliding-popup").html(Drupal.settings.popup_message.popup_html_agreed).animate({bottom: 0}, Drupal.settings.popup_message.popup_delay)
          Drupal.popup_message.attachEvents();
        }
        if(status == 1) {
          $("#sliding-popup").remove();
        }
      ;})
    }
    Drupal.popup_message.setStatus(value);
  }

  Drupal.popup_message.setStatus = function(status) {
    var date = new Date();
    date.setDate(date.getDate() + 100);
    var cookie = "cookie-agreed=" + status + ";expires=" + date.toUTCString() + ";path=" + Drupal.settings.basePath;
    if(Drupal.settings.popup_message.domain) {
      cookie += ";domain="+Drupal.settings.popup_message.domain;
    }
    document.cookie = cookie;
  }

  Drupal.popup_message.hasAgreed = function() {
    var status = Drupal.popup_message.getCurrentStatus();
    if(status == 1 || status == 2) {
      return true;
    }
    return false;
  }


  /**
   * Verbatim copy of Drupal.comment.getCookie().
   */
  Drupal.popup_message.getCookie = function(name) {
    var search = name + '=';
    var returnValue = '';

    if (document.cookie.length > 0) {
      offset = document.cookie.indexOf(search);
      if (offset != -1) {
        offset += search.length;
        var end = document.cookie.indexOf(';', offset);
        if (end == -1) {
          end = document.cookie.length;
        }
        returnValue = decodeURIComponent(document.cookie.substring(offset, end).replace(/\+/g, '%20'));
      }
    }

    return returnValue;
  };
  
  Drupal.popup_message.cookiesEnabled = function() {
    var cookieEnabled = (navigator.cookieEnabled) ? true : false;
      if (typeof navigator.cookieEnabled == "undefined" && !cookieEnabled) { 
        document.cookie="testcookie";
        cookieEnabled = (document.cookie.indexOf("testcookie") != -1) ? true : false;
      }
    return (cookieEnabled);
  }
  
})(jQuery);