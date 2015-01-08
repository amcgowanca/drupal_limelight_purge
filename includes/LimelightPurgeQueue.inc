<?php
/**
 * @file
 * LimelightPurgeQueue.inc
 */

require_once DRUPAL_ROOT . '/modules/system/system.queue.inc';

/**
 * Reliable queue class for the Limelight Purge URL entries.
 */
class LimelightPurgeQueue extends SystemQueue {
  /**
   * {@inheritdoc}
   */
  public function createItem($url) {
    $query = db_insert('queue')->fields(array(
      'name' => $this->name,
      'data' => $url,
      'created' => time(),
    ));
    return (bool) $query->execute();
  }

  /**
   * {@inheritdoc}
   */
  public function claimItem($lease_time = 30) {
    while (TRUE) {
      $item = db_query_range('SELECT data, item_id FROM {queue} q WHERE expire = 0 AND name = :name ORDER BY created ASC', 0, 1, array(':name' => $this->name))->fetchObject();
      if ($item) {
        $update = db_update('queue')->fields(array(
            'expire' => time() + $lease_time,
          ))
          ->condition('item_id', $item->item_id)
          ->condition('expire', 0);
        if ($update->execute()) {
          return $item;
        }
      }
      else {
        return FALSE;
      }
    }
  }

  /**
   * Returns a boolean indicating whether or not the specified URL exists.
   *
   * @access public
   *
   * @param string $url
   *   The URL to check if it exists within the queue.
   *
   * @return bool
   *   Returns TRUE if an item exists with the URL, otherwise FALSE.
   */
  public function itemExists($url) {
    $exists = db_query('SELECT item_id FROM {queue} WHERE name = :name AND data = :url', array(':name' => $this->name, ':url' => $url))->fetchObject();
    if ($exists) {
      return TRUE;
    }
    return FALSE;
  }
}
