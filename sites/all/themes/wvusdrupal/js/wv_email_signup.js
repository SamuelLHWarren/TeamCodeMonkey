/**
 * @file
 * Handles the ajax submission of the email signup form.
 *
 * @ingroup wv_email_signup
 */

(function($) {
  Drupal.behaviors.emailSignup = {

    attach : function(context, settings) {
      // Process the footer subscription form.
      $('#footer-subscription-form').submit(function() {

        var email = $('#subscription-email').val();

        // Only process if this is a valid email format.
        if (isEmail(email)) {

          // Submit the form via AJAX.
          $.ajax({

            url : '/service/jsonp?callback=?',
            dataType : 'jsonp',
            "jsonp": 'callback',

            data : {
              subscription : email,
              jsonservice: 'http://www.worldvision.org/wv-email-signup/process'
            },
        
            success : function(data) {
              
              // Add message div if it doesn't already exist.
              if (!$('#footer-subscription-form .messages').length) {
                $('#subscription-email').after('<div class="messages"></div>');
              }

              // An error occurred.
              if (data.error == 'true') {
                $('#footer-subscription-form .messages').removeClass('status').addClass('error').html(data.message);
              } else {

                // Success.
                $('#footer-subscription-form .messages').removeClass('error').addClass('status').html(data.message);

                // Remove the sign up button.
                $('#footer-subscription-form input.btn').remove();
              }
            },
            error : function() {

              $('#footer-subscription-form .messages').removeClass('status').addClass('error').html('Sorry! An error occurred while processing your email. Please try again later.');
            },
            timeout: 15000
          });
        } else {
          // Invalid email format!
          // Add message div if it doesn't already exist.
          if (!$('#footer-subscription-form .messages').length) {
            $('#subscription-email').after('<div class="messages"></div>');
          }
          $('#footer-subscription-form .messages').removeClass('status').addClass('error').html('Sorry! We didn\'t recognize that email format. Please try again.');
        }

        // Prevent the form from submitting.
        return false;
      });

    }
  };

  /**
   * Checks if this is a valid email address.
   *
   * @param string email
   *   A user-inputted email address.
   *
   * @return bool
   *   True if properly formatted, otherwise false.
   */
  function isEmail(email) {
    var regex = /^([a-zA-Z0-9_\.\-\+])+\@(([a-zA-Z0-9\-])+\.)+([a-zA-Z0-9]{2,4})+$/;
    return regex.test(email);
  }

})(jQuery);
