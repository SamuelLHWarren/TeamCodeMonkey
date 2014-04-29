<header id="page-header">
  <div class="container" >
        <div class="row">
          <div id="logo-box" class="span7">
            
              <div class="row">
                <div id="logo" class="span2">
                  <a href="http://www.worldvision.org" title="World Vision USA">World Vision USA</a>
                </div>
                <div id="slogan" class="span5">
                  <a href="http://www.worldvision.org" title="Building a better world for children">Building a better world for children</a>
                </div>
              </div>
          </div>
          <div id="service-box" class="span5 pull-right">
            <div class="row text-center">
             <form action="http://www.worldvision.org/search" method="get" id="search-form" accept-charset="UTF-8" novalidate="true" class="form-inline pull-right">
                <input id="search-keyword" name="keyword" class="input-xlarge" placeholder="SEARCH" type="text" title="Search worldvision.org">
                <button type="submit" class="add-on" title="Search"><i class="icon-search icon-2x"></i></button>
              </form>
            </div>
            <div class="row top-buffer">
              <div class="span3">
                <ul id="eco-sso" class="inline link-divider">
                  <li><a href="https://donate.worldvision.org/OA_HTML/xxwvibeCZzpEntry.jsp?go=cart" class="text" id="header-cart-count"><i class="icon-shopping-cart icon-2x"></i><span class="link-underline">MY BASKET (<span class="cart-count">0</span>)</span></a></li>
                  <li> <a href="http://my.worldvision.org/user/login" class="text" id="header-sign-in">SIGN IN</a>  </li>
                </ul>
              </div>
              <div class="span2">
                <ul id="social-media" class="inline pull-right">
                    <li>
                      <a href="https://www.facebook.com/worldvision" target="_blank" title="World Vision USA Facebook">
                        <span class="icon-stack icon-2x">
                          <i class="icon-sign-blank icon-light"></i>
                          <i class="icon-facebook-sign"></i>
                        </span>
                        
                      </a>
                    </li>
                    <li>
                      <a href="https://twitter.com/WorldVisionUSA" target="_blank" title="World Vision USA Twitter">
                        <span class="icon-stack icon-2x">
                          <i class="icon-sign-blank icon-light"></i>
                          <i class="icon-twitter-sign"></i>
                        </span>
                      </a>
                    </li>
                    <li>
                      <a href="http://www.youtube.com/user/WorldVisionUSA" target="_blank" title="World Vision USA YouTube">
                        <span class="icon-stack icon-2x">
                          <i class="icon-sign-blank icon-light"></i>
                          <i class="icon-youtube-sign"></i>
                        </span>
                      </a>
                    </li>
                    <li class="blog-icon-li">
                      <a href="http://blog.worldvision.org" title="World Vision Blog" class="blog-icon"></a>
                    </li>
                </ul>
              </div>
            </div>
          </div>
        </div>

<?php if ($page['header']): ?>
  <?php print render($page['header']); ?>
<?php endif; ?>
    </div>

  <?php if($page['navigation']): ?>
    <?php print render($page['navigation']); ?>
  <?php endif; ?>
</header>

