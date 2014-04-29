(function ($) {

    var globalNavVars = {};

    $(document).ready(function ($) {

        var vars = wvcoreSetEnvironmentVariables();
		    globalNavVars = vars;
        

        /* Update urls to reflect current environment. */
        if (vars.suffix != '') {
            wvcoreSetEnvironmentUrls(vars);
        }

        /* Main Menu > Dropdown > Title Link */
        $('.dropdown-title a').removeAttr('data-toggle data-hover').removeClass('dropdown-toggle');

        /* Same 'isTablet' check from mobile redirect module */
        if( /iPad/i.test(navigator.userAgent) || ( /Android/i.test(navigator.userAgent) && !/Mobile/i.test(navigator.userAgent) ) ) {
            var istore = 'donate.worldvision.org';
            var myWV = 'my.worldvision.org';
            if(vars.suffix != '') {
              istore = vars.istore + '.worldvision.org';
              myWV = 'my' + vars.suffix + '.worldvision.org';
            }


            // This functions as the blur event.
            $(document).on('touchstart', function(e) {
                if(!(e.target.href != undefined && (e.target.href.indexOf(baseUrl) != -1 || e.target.href.indexOf('http://' + istore) != -1 || e.target.href.indexOf('http://' + myWV) != -1 || e.target.href.indexOf('https://' + istore) != -1 || e.target.href.indexOf('https://' + myWV) != -1) && $(e.target).parents('#nav').length > 0)) {
                  $('.navbar .dropdown').removeClass('open');
                }
            });

            // This overrides the blur event, and sets the toggle.
            $('.navbar .dropdown > a').on('touchstart', function(e){

                // Remove open class from all other lis.
                $('.navbar .dropdown').removeClass('open');
                $(this).parent().addClass('open');
                $(this).parent().focus();

                return false;
            });


        } else {
            /* Not a tablet, so Main Menu click follows href instead of opening dropdown */
            $('.navbar .dropdown > a').click(function(){
               location.href = this.href;
            });
        };

				/* Set iStore and myWv active trail in global nav as needed */
				if(vars.myWvRes) {
					 $('#nav a').each(function() {
					 if(vars.myWvPatt.test($(this).attr('href'))) {
						 $(this).parent().addClass('active-trail');
						 $(this).addClass('active-trail');
					 }
				 });
				}

				if(vars.iStoreRes) {
					 $('#nav a').each(function() {
					 if(vars.iStorePatt.test($(this).attr('href'))) {
						 $(this).parent().addClass('active-trail');
						 $(this).addClass('active-trail');
					 }
				 });
				}


        /* Set the user login state in the header. */
        wvcoreSetUserLoginState(vars);

        /* Submit validator for disaster alert forms. */
        $('#xxwvotheramt').bind("keypress", function (event) {
            var key = event.keyCode || event.charCode;
            if (key == 8 || key == 46) {
                return true;
            }

            var charCode = event.which;
            var keyChar = String.fromCharCode(charCode);
            return !isNaN(keyChar);


        });

        /* Make sure our rounded corners trigger a form submit. */
        $('#wv-disaster-alert-alert-donate-form .donations-submit-wrapper-left').click(function() {
          $('#wv-disaster-alert-alert-donate-form').trigger('submit');
        });

        $('#wv-disaster-alert-alert-donate-form').submit(function () {
            var amount = $('#xxwvotheramt').val().replace('$', '').replace(',', '');
            var error = '';

            if (isNaN(amount)) {
                error = 'Please enter only numbers.';
            } else if (!amount || amount < 10) {
                error = 'Please enter a donation of $10 or more.';
            } else if (amount > 100000) {
                error = 'Please enter a donation amount of $100,000 or less.';
            } else {
                $('#xxwvotheramt').val(amount);
            }

            if(error != '') {
              /* Check if modal has been created, and add if not. */
              if($('#alert-modal').length == 0) {
                $('#block-disaster-alerts').append('<div id="alert-modal" class="modal hide fade in" style="display: none; ">' +
                  '<div class="modal-body">' +
                  '<a class="close" data-dismiss="modal">x</a>' +
                  //'<h4 style="color: #444;">Error!</h4>' +
                  '<p class="message" style="color: #444;"></p>' +
                  '</div>' +
                  '<div class="modal-footer">' +
                  '<a href="#" class="btn" data-dismiss="modal">OK</a>' +
                  '</div>' +
                  '</div>');
              }

              $('#alert-modal .modal-body .message').html(error);
              $('#alert-modal').modal();
              return false;
            }
        });

        // adding IE support for placeholder html5 attribute
				if(!$.support.placeholder) {
					$('#search-keyword').focus(function () {
						if ($(this).attr('placeholder') != '' && $(this).val() == $(this).attr('placeholder')) {
							$(this).val('').removeClass('hasPlaceholder');
						}
					}).blur(function () {
						if ($(this).attr('placeholder') != '' && ($(this).val() == '' || $(this).val() == $(this).attr('placeholder'))) {
							$(this).val($(this).attr('placeholder')).addClass('hasPlaceholder');
						}
					});
					$('#search-keyword').blur();
					$('#search-form').submit(function () {
						$(this).find('.hasPlaceholder').each(function() { $(this).val(''); });
					});
				}

				// Mark external links.
        $('#block-disaster-alerts a').each(function() {
          // Exclude from feature headers and images.
          if($(this).has('img').length == 0 && $(this).has('h3').length == 0) {
            if($(this).attr('target') == '_blank') {
              $(this).append('<span class="external-link">External Link</span>');
            }
          }
        });
        
        // attach onclick event to Sign Out link
        $('#header-sign-in').click(function (e) {
        	if ($('#header-sign-in').text().toLowerCase()=='sign out') {
	        	wvcoreLogOutUser(vars);
  	      	e.preventDefault();
  	      }
				});
        

    });

    var authResults = {};
    var unAuthResults = {};

    /**
     * Performs an ajax call to mywv and eComm to log out
     */
    function wvcoreLogOutUser(vars) {
				logOutMywv(vars);
				logOuteComm(vars);
    }

    /**
     * unauth in mywv
     */
    function logOutMywv(vars) {
        $.ajax({
            "url": "https://my" + vars.suffix + ".worldvision.org/api/unAuth",
            "dataType": "jsonp",
            "cache": "false",
            "jsonp": 'jsoncallback',
            "success": function (data) {
                unAuthResults.mywvDone = true;
                unAuthResults.mywvResults = data.auth;
                if (unAuthResults.eCommDone) {
                	logOutChangeGlobalNav(vars);
                }
            },
            "error": function (d, msg) {
                unAuthResults.mywvDone = true;
                unAuthResults.mywvResults = 'error';
                if (unAuthResults.eCommDone) {
                	logOutChangeGlobalNav(vars);
                }
            },
            timeout: 15000
        });
    }

    /**
     * unauth in eComm
     */
    function logOuteComm(vars) {
        $.ajax({
            "url": "https://" + vars.istore + ".worldvision.org/OA_HTML/xxwv2WSAuthentication.jsp?action=logout",
            "dataType": "jsonp",
            "cache": "false",
            "jsonp": 'jsoncallback',
            "success": function (data) {
                unAuthResults.eCommDone = true;
                unAuthResults.eCommResults = data.data[0].authenticated;
                if (unAuthResults.mywvDone) {
                	logOutChangeGlobalNav(vars);
                }
            },
            "error": function (d, msg) {
                unAuthResults.eCommDone = true;
                unAuthResults.eCommResults = 'error';
                if (unAuthResults.mywvDone) {
                	logOutChangeGlobalNav(vars);
                }
            },
            timeout: 15000
        });
    }

    /**
     * Changes global nav after logout
     */
    function logOutChangeGlobalNav(vars) {
				if (!unAuthResults.mywvResults && unAuthResults.eCommResults=='N') {// logged out successfully
					var logOutUrl = 'http://'+vars.core+'.worldvision.org';
					if (vars.myWvRes) {// in mywv
						logOutUrl = 'http://my'+vars.suffix+'.worldvision.org';
					} else if (vars.iStoreRes) {// in istore
						logOutUrl = 'http://'+vars.istore+'.worldvision.org';
					} else if (vars.scoRes) {// in sco
						logOutUrl = 'http://'+vars.istore+'.worldvision.org/commerce';
					}
					window.location = logOutUrl;
				} else {// there was an error logging out of one system
					alert('There was an error trying to Sign Out - Please try again');
				}
    }

    /**
     * Performs an ajax call to mywv and eComm and returns user login status and cart count.
     */
    function wvcoreSetUserLoginState(vars) {
        /* Set the cart url. */
        $('#header-cart-count').attr('href', 'https://' + vars.istore + '.worldvision.org/OA_HTML/xxwvibeCZzpEntry.jsp?go=cart');
				checkMywvAuth(vars);
				checkeCommAuth(vars);
    }

    /**
     * Changes global nav links/text based on results of auth status for mywv and eComm
     */
    function wvcoreChangeGlobalNav(vars) {
				// set defaults
				var authText = 'Sign In';
				var authLink = 'http://my' + vars.suffix + '.worldvision.org/user/login';
				
				// if mywv - then check to see if we are auth in mywv
				if (vars.myWvRes) {// we are in mywv
					if (authResults.mywvResults) {// change link to Sign Out
						authText = 'Sign Out';
						authLink = 'http://my' + vars.suffix + '.worldvision.org/logout';
					}
				} else {
					if (!authResults.eCommResults) {// error on eComm auth
						authLink = 'http://www.worldvision.org/content.nsf/pages/gc-redirect?open';
					} else if (authResults.eCommResults.authenticated==="true") {// logged into eComm
						authText = 'Sign Out';
						authLink = 'http://my' + vars.suffix + '.worldvision.org/logout';
					}
				}

				$('#header-sign-in').html(authText);
				$('#header-sign-in').attr('href', authLink);
				$('.cart-count').html(authResults.eCommResults.cartItemCount);
    }

    /**
     * check auth status in mywv
     */
    function checkMywvAuth(vars) {
        $.ajax({
            "url": "https://my" + vars.suffix + ".worldvision.org/api/checkAuth",
            "dataType": "jsonp",
            "cache": "false",
            "jsonp": 'jsoncallback',
            "success": function (data) {
                authResults.mywvDone = true;
                authResults.mywvResults = data.auth;
                if (authResults.eCommDone) {
                	wvcoreChangeGlobalNav(vars);
                }
            },
            "error": function (d, msg) {
                authResults.mywvDone = true;
                authResults.mywvResults = false;
                if (authResults.eCommDone) {
                	wvcoreChangeGlobalNav(vars);
                }
            },
            timeout: 15000
        });
    }

    /**
     * check auth status in eComm
     */
    function checkeCommAuth(vars) {
        $.ajax({
            "url": "https://" + vars.istore + ".worldvision.org/OA_HTML/xxwv2Session.jsp",
            "dataType": "jsonp",
            "cache": "false",
            "jsonp": 'jsoncallback',
            "success": function (data) {
                authResults.eCommDone = true;
                authResults.eCommResults = data.userSession;
                if (authResults.mywvDone) {
                	wvcoreChangeGlobalNav(vars);
                }
            },
            "error": function (d, msg) {
                authResults.eCommDone = true;
                authResults.eCommResults = false;
                if (authResults.mywvDone) {
                	wvcoreChangeGlobalNav(vars);
                }
            },
            timeout: 15000
        });
    }

    /**
     * Sets a variables based on the current environment.
     */
    function wvcoreSetEnvironmentVariables() {
        var bits = window.location.href.split('/');
        var vars = {};

        switch (bits[2]) {
            case 'coredev.worldvision.org':
            case 'dev1.worldvision.org':
            case 'onyx.worldvision.org':
            case 'mydev.worldvision.org':
            case 'd7.local':
                vars.suffix = 'dev';
                vars.core = 'coredev';
                vars.istore = 'onyx';
                break;

            case 'qa1.worldvision.org':
            case 'jade.worldvision.org':
            case 'myqa01.worldvision.org':
                vars.suffix = 'qa01';
                vars.core = 'qa1';
                vars.istore = 'jade';
                break;

            case 'corestg.worldvision.org':
            case 'stg1.worldvision.org':
            case 'opal.worldvision.org':
            case 'mystage.worldvision.org':
                vars.suffix = 'stage';
                vars.core = 'stg1';
                vars.istore = 'opal';
                break;

            default:
                vars.suffix = '';
                vars.istore = 'donate';
                vars.core = 'www';
                break;
        }
        
 				var curUrl = document.URL;
				var myWvPatt=/my\w*\.worldvision\.org/g;
				var iStorePatt=/\.worldvision\.org\/OA_HTML/;
				var scoPatt=/\.worldvision\.org\/commerce/;
				vars.myWvRes=myWvPatt.test(curUrl);
				vars.iStoreRes=iStorePatt.test(curUrl);
				vars.scoRes=scoPatt.test(curUrl);
				vars.myWvPatt = myWvPatt;
				vars.iStorePatt = iStorePatt;
				vars.scoPatt = scoPatt;

        return vars;
    }

    /**
     * Replaces url prefixes for the current environment.
     */
    function wvcoreSetEnvironmentUrls(vars) {
        $('a').each(function () {
            if ($(this).attr('href') != undefined) {
                var newHref = $(this).attr('href').replace('//donate.', '//' + vars.istore + '.').replace('//my.', '//my' + vars.suffix + '.');
                $(this).attr('href', newHref);
            }
        });
        $('form').each(function () {
            if ($(this).attr('action') != undefined) {
                var newAction = $(this).attr('action').replace('//www.', '//' + vars.core + '.').replace('//donate.', '//' + vars.istore + '.').replace('//my.', '//my' + vars.suffix + '.');
                $(this).attr('action', newAction);
            }
        });
    }

})(jQuery);
