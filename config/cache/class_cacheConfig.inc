<?php
/*
  This code is part of FusionDirectory (http://www.fusiondirectory.org/)

  Copyright (C) 2012-2020 FusionDirectory

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
*/

class cacheConfig extends simplePlugin
{
  static function plInfo (): array
  {
    return [
      'plShortName'     => _('Cache configuration'),
      'plDescription'   => _('FusionDirectory Cache plugin configuration'),
      'plObjectClass'   => ['fdCachePluginConf'],
            'plObjectType'    => ['configuration'],
      'plPriority'      => 10,
      'plProvidedAcls'  => parent::generatePlProvidedAcls(static::getAttributesInfo())
    ];
  }

  static function getAttributesInfo (): array
  {
    return [
      'cache' => [
        'class' => ['fullwidth'],
        'name'  => _('Cache'),
        'attrs' => [
            new OrderedArrayAttribute(
                new CharSeparatedCompositeAttribute(
                  _('Mapping list'),
                  'fdCacheDataMapping',
                  [
                    new stringAttribute(
                      _('Plugin'), _('Plugin Mapping relating to'),
                      'fdCacheDataMapping_plugin', TRUE
                    ),
                    new stringAttribute(
                        _('Section'), _('Plugin Section relating to'),
                        'fdCacheDataMapping_section', TRUE
                      ),
                      new stringAttribute(
                        _('Variable'), _('Plugin Variable relating to'),
                        'fdCacheDataMapping_variable', TRUE
                      ),                                          
                      new stringAttribute(
                        _('Type'), _('type of variable relating to'),
                        'fdCacheDataMapping_type', TRUE
                      ),
                      new BooleanAttribute(
                        _('Dashboard'), _('Display it on dashboard'),
                        'fdCacheDataMapping_dashboard', FALSE,
                        FALSE
                      )
                  ],
                  '|',
                  '',
                  _('Mapping')
                ),
                FALSE,
                [],
                TRUE
                )
        ]
      ],
    ];
  }
}
