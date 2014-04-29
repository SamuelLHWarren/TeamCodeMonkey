<?php if ($page['footer']): ?>
  <footer id="page-footer">
      <div class="container">
        <div class="row">
          <div class="span12">
            <div class="footer-menu">
              <?php print render($page['footer']['menu_block_3']); //about us menu block ?>
            </div>
            <div class="footer-menu">
              <?php print render($page['footer']['menu_block_4']); //our impact menu block ?>
            </div>
            <div class="footer-menu">
              <?php print render($page['footer']['menu_block_5']); //how you can help block ?>
            </div>

            <div class="footer-menu">
              <?php print render($page['footer']['block_9']); ?>
            </div>
            <div class="footer-menu">
                  <?php print render($page['footer']['block_10']); ?>
            </div>
          </div>
        </div>
        <div class="row">
          <div class="span5">
            <?php print render($page['footer']['block_2']); ?>
          </div>
          <div id="footer-trust" class="span7">
            <?php print render($page['footer']['block_8']); ?>
          </div>
        </div>
      </div>
    </footer>
<?php endif; ?>
