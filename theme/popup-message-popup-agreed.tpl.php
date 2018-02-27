<?php

/**
 * @file
 * Template for a pop-up informing they have already agreed to cookies.
 *
 * When overriding this template it is important to note that jQuery will use
 * the following classes to assign actions to buttons:
 *
 * hide-popup-button - destroy the pop-up
 * find-more-button  - link to an information page
 *
 * Variables available:
 * - $message:  Contains the text that will be display whithin the pop-up
 * - $hide_button: Contains hide butlon title
 * - $find_more_button: Contains find more button title
 */
?>
<div class="popup-message-content agreed">
  <div id="popup-message-text">
    <?php print $message ?>
  </div>
  <div id="popup-message-buttons">
    <button type="button" class="popup-message-hide-popup-button"><?php print $hide_button; ?></button>
    <button type="button" class="popup-message-find-more-button" ><?php print $find_more_button; ?></button>
  </div>
</div>
