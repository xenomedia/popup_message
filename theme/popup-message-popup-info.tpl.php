<?php

/**
 * @file
 * Template for a pop-up prompting user to give consent. Cookie set on dismiss.
 *
 * When overriding this template it is important to note that jQuery will use
 * the following classes to assign actions to buttons:
 *
 * agree-button      - agree to setting cookies
 * find-more-button  - link to an information page
 *
 * Variables available:
 * - $message:  Contains the text that will be display whithin the pop-up
 * - $agree_button: Contains agree button title
 * - $disagree_button: Contains disagree button title
 */
?>
<div class="popup-message-content info">
  <div id="popup-message-text">
    <?php print $message ?>
  </div>
  <div id="popup-message-buttons">
    <button type="button" class="popup-message-agree-button"><?php print $agree_button; ?></button>
    <button type="button" class="popup-message-find-more-button"><?php print $disagree_button; ?></button>
  </div>
</div>
