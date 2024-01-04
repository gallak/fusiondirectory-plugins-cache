<?php
/*
  This code is part of FusionDirectory (http://www.fusiondirectory.org/)
  Copyright (C) 2016-2017  FusionDirectory
  Copyright (C) 2021-2024  Antoine Gallavardin

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


class simpleRemotePlugin extends simplePlugin {



public function convertTransformMap($ressource){

  global $config;
  $struct=array();
  foreach ($config->get_cfg_value('CacheDataMapping') as $map ){
    $mapArray=explode("|",$map);
    if ($ressource == $mapArray[0]){
      $struct[$mapArray[1]][$mapArray[2]]=$mapArray[3];
    }
  }
  return($struct);

}


public function convertTransformMapDashbord($ressource){

  global $config;
  $struct=array();
  foreach ($config->get_cfg_value('CacheDataMapping') as $map ){
    $mapArray=explode("|",$map);
    if ($ressource == $mapArray[0]){
      if ($mapArray[4] == "TRUE") {
        $struct[$mapArray[1]][$mapArray[2]]=$mapArray[3];
      }
    }
  }
  return($struct);

}

  // return cache content
  function getRemoteObjectCache(){
    return(unserialize(gzinflate($this->attrs['fdCacheData'][0])));   
  }
  
  // update cache content
  function updateRemoteObjectCache($value){
    array_push($this->attrs['objectClass'], 'fdCache');
    $this->attrs['objectClass']=array_unique($this->attrs['objectClass']);
    $this->attrs['fdCacheData']=gzdeflate(serialize($value)); 
      
  }


  function deleteRemoteCache(){
    // FIXME
    //$this->removeAttribute('nutNode','fdCacheData');
    //$this->attrs['objectClass']=array_diff($this->attrs['objectClass'],['fdCache']);
    //unset($this->attributesAccess['remoteData']);
    //unset($this->attrs['remoteData']);

  }
 

  protected function prepare_save (): array
  {
    $errors = parent::prepare_save();
  
    if (!empty($errors)) {
      return $errors;
    }
    if ( $this->remoteCacheAction == "UPDATE"){
      //refresh ressource
      $this->remoteData=$this->remoteHandler->refreshRessource();
      // format ressource
      $this->remoteData=$this->remoteHandler->renderOneRsc($this->remoteData,$this->remoteRenderingMap);
      
      $this->updateRemoteObjectCache($this->remoteData);
    }

    if ( $this->remoteCacheAction == "CLEAR"){
      $this->deleteRemoteCache();
    }
    if (empty($this->remoteCacheAction)){
      $this->updateRemoteObjectCache($this->remoteData);
    }
    return $errors;
  }


}


