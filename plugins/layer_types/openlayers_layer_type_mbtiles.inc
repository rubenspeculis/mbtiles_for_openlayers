<?php
/**
 * @file
 * Mbtiles Layer Type
 */

/**
 * OpenLayers Mbtiles Layer Type class
 */
class openlayers_layer_type_mbtiles extends openlayers_layer_type {

  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'layer_handler' => 'mbtiles',
      'type' => 'png',
      'inverse' => TRUE,
      'wrapDateLine' => FALSE,
      'zoomOffset' => 0,
      'url' => ''
    ) + parent::options_init();
  }

  /**
   * Options form which generates layers
   */
  function options_form($defaults = array()) {
    return array(
      'url' => array(
        '#type' => 'textarea',
        '#title' => t('Base URL'),
        '#default_value' => !empty($this->data['url']) ? implode("\n", $this->data['url']) : '',
        '#description' => t('This is the base URL of the Mbtiles service.  For example, if this was your tile scheme URL: http://example.com/layer_name/{z}/{y}/{x}.png, then <em>http://example.com/</em> would be the Base URL.'),
      ),
      'layername' => array(
        '#type' => 'textfield',
        '#title' => t('Layer Name'),
        '#default_value' => isset($this->data['layername']) ?
          $this->data['layername'] : '',
        '#description' => t('This is the base URL of the Mbtiles service.  For example, if this was your tile scheme URL: http://example.com/layer_name/{z}/{y}/{x}.png, then <em>layer_name</em> would be the Layer Name.'),
      ),
      'type' => array(
        '#type' => 'select',
        '#title' => t('File Format'),
        '#options' => array(
          'png' => 'png',),
        '#default_value' => isset($this->data['type']) ? $this->data['type'] : 'png'
      ),
      'resolutions' => array(
        '#type' => 'select',
        '#multiple' => TRUE,
        '#options' => array_combine(
          array_map('strval', openlayers_get_resolutions('EPSG:900913')),
          range(0, 21)
        ),
        '#title' => t('Zoom Level Range'),
        '#default_value' => isset($this->data['resolutions']) ?
          $this->data['resolutions'] :
          array_map('strval', openlayers_get_resolutions('EPSG:900913')),
        '#description' => t('The available zoom levels for the tiles.'),
      ),
      'wrapDateLine' => array(
        '#type' => 'checkbox',
        '#title' => t('Wrap Dateline'),
        '#default_value' => isset($this->data['wrapDateLine']) ?
          $this->data['wrapDateLine'] : FALSE,
        '#description' => t('Wrapping the dateline will cause the map to appear to repeat itself when going east or west.  This may not be supported by all tilesets.'),
      ),
      'inverse' => array(
        '#type' => 'checkbox',
        '#title' => t('Is the Y coordinate flipped ?'),
        '#default_value' => isset($this->data['inverse']) ? $this->data['inverse'] : TRUE,
        '#description' => t('The purpose of this layer is to flip the Y axis to display mbtiles correctly'),
      ),
    );
  }

  function options_form_validate($form, &$form_state) {
  }

  function options_form_submit($form, &$form_state) {
    parent::options_form_submit($form, $form_state);
    $form_state['values']['data']['url'] = explode("\n", $form_state['values']['data']['url']);
    $form_state['values']['data']['resolutions'] = array_map('floatval', array_values($form_state['values']['data']['resolutions']));
    $form_state['values']['data']['wrapDateLine'] = (bool) $form_state['values']['data']['wrapDateLine'];
    $form_state['values']['data']['inverse'] = (bool) $form_state['values']['data']['inverse'];
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_add_js(drupal_get_path('module', 'mbtiles_for_openlayers') . '/plugins/layer_types/openlayers_layer_type_mbtiles.js');
  }
}
