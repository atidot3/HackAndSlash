/*
Navicat MySQL Data Transfer

Source Server         : home
Source Server Version : 50617
Source Host           : localhost:3306
Source Database       : hackandslash

Target Server Type    : MYSQL
Target Server Version : 50617
File Encoding         : 65001

Date: 2016-03-01 15:10:42
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for accounts
-- ----------------------------
DROP TABLE IF EXISTS `accounts`;
CREATE TABLE `accounts` (
  `AccountID` int(10) NOT NULL AUTO_INCREMENT,
  `Username` varchar(20) DEFAULT NULL,
  `AccountPW` varchar(100) DEFAULT NULL,
  `acc_status` enum('block','active') DEFAULT 'active',
  `money` int(10) DEFAULT '0',
  `email` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`AccountID`)
) ENGINE=InnoDB AUTO_INCREMENT=0 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for characters
-- ----------------------------
DROP TABLE IF EXISTS `characters`;
CREATE TABLE `characters` (
  `CharID` int(10) NOT NULL AUTO_INCREMENT,
  `CharName` varchar(20) NOT NULL,
  `AccountID` int(10) DEFAULT NULL,
  `Level` tinyint(3) DEFAULT '1',
  `Exp` int(10) DEFAULT '0',
  `MaxExpInThisLevel` int(10) DEFAULT '0',
  `Class` tinyint(2) DEFAULT NULL,
  `CurLocX` float(10,5) DEFAULT '-1500.00000',
  `CurLocY` float(10,5) DEFAULT '500.00000',
  `CurLocZ` float(10,5) DEFAULT '200.00000',
  `CurDirX` float(10,5) DEFAULT '200.00000',
  `CurDirY` float(10,5) DEFAULT '0.00000',
  `CurDirZ` float(10,5) DEFAULT '1.00000',
  `WorldID` int(10) DEFAULT '0',
  `BaseStr` int(3) DEFAULT '1',
  `LastStr` int(3) DEFAULT '1',
  `BaseCon` int(3) DEFAULT '1',
  `LastCon` int(3) DEFAULT '1',
  `BaseDex` int(3) DEFAULT '1',
  `LastDex` int(3) DEFAULT '1',
  `BaseInt` int(3) DEFAULT '1',
  `LastInt` int(3) DEFAULT '1',
  `BaseEng` int(3) DEFAULT '1',
  `LastEng` int(3) DEFAULT '1',
  `BaseMaxLP` int(5) DEFAULT '100',
  `LastMaxLP` int(5) DEFAULT '100',
  `BaseMaxEP` int(5) DEFAULT '100',
  `LastMaxEP` int(5) DEFAULT '100',
  `BaseMaxRP` int(5) DEFAULT '100',
  `LastMaxRP` int(5) DEFAULT '100',
  `BaseLpRegen` int(5) DEFAULT '0',
  `LastLpRegen` int(5) DEFAULT '0',
  `BaseEpRegen` int(5) DEFAULT '0',
  `LastEpRegen` int(5) DEFAULT '0',
  `BaseRpRegen` int(5) DEFAULT '0',
  `LastRpRegen` int(5) DEFAULT '0',
  `BasePhysicalOffence` int(5) DEFAULT '0',
  `LastPhysicalOffence` int(5) DEFAULT '0',
  `BasePhysicalDefence` int(5) DEFAULT '0',
  `LastPhysicalDefence` int(5) DEFAULT '0',
  `BaseEnergyOffence` int(5) DEFAULT '0',
  `LastEnergyOffence` int(5) DEFAULT '0',
  `BaseEnergyDefence` int(5) DEFAULT '0',
  `LastEnergyDefence` int(5) DEFAULT '0',
  `BaseAttackRate` int(5) DEFAULT '0',
  `LastAttackRate` int(5) DEFAULT '0',
  `BaseDodgeRate` int(5) DEFAULT '0',
  `LastDodgeRate` int(5) DEFAULT '0',
  `BaseBlockRate` int(5) DEFAULT '0',
  `LastBlockRate` int(5) DEFAULT '0',
  `BasePhysicalCriticalRate` int(5) DEFAULT '0',
  `LastPhysicalCriticalRate` int(5) DEFAULT '0',
  `BaseEnergyCriticalRate` int(5) DEFAULT '0',
  `LastEnergyCriticalRate` int(5) DEFAULT '0',
  `LastRunSpeed` float(10,5) DEFAULT '8.00000',
  `BaseAttackSpeedRate` int(5) DEFAULT '0',
  `LastAttackSpeedRate` int(5) DEFAULT '0',
  `BaseAttackRange` float(10,5) DEFAULT '0.00000',
  `LastAttackRange` float(10,5) DEFAULT '0.00000',
  `PhysicalCriticalDamageBonusRate` float(10,5) DEFAULT '0.00000',
  `EnergyCriticalDamageBonusRate` float(10,5) DEFAULT '0.00000',
  `CurLP` int(10) DEFAULT '100',
  `CurEP` int(10) DEFAULT '100',
  `CurRP` int(10) DEFAULT '100',
  PRIMARY KEY (`CharID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for experiance
-- ----------------------------
DROP TABLE IF EXISTS `experiance`;
CREATE TABLE `experiance` (
  `ID` int(10) NOT NULL AUTO_INCREMENT,
  `Level` int(10) NOT NULL,
  `MaxExpInThisLevel` int(10) NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=0 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for friendlist
-- ----------------------------
DROP TABLE IF EXISTS `friendlist`;
CREATE TABLE `friendlist` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `account` varchar(20) DEFAULT NULL,
  `friend` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=0 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for item_template
-- ----------------------------
DROP TABLE IF EXISTS `item_template`;
CREATE TABLE `item_template` (
  `""` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `ID` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `class` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `subclass` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `name` varchar(255) NOT NULL DEFAULT '',
  `Quality` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `BuyPrice` bigint(20) NOT NULL DEFAULT '0',
  `SellPrice` int(10) unsigned NOT NULL DEFAULT '0',
  `InventoryType` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `AllowableClass` int(11) NOT NULL DEFAULT '-1',
  `RequiredLevel` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `count` int(11) NOT NULL DEFAULT '0',
  `maxcount` int(11) NOT NULL DEFAULT '0',
  `stackable` int(11) DEFAULT '1',
  `dmg_min1` float NOT NULL DEFAULT '0',
  `dmg_max1` float NOT NULL DEFAULT '0',
  `dmg_type1` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `dmg_min2` float NOT NULL DEFAULT '0',
  `dmg_max2` float NOT NULL DEFAULT '0',
  `dmg_type2` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `armor` smallint(5) unsigned NOT NULL DEFAULT '0',
  `holy_res` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `fire_res` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `nature_res` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `frost_res` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `shadow_res` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `arcane_res` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `stat_type1` int(10) NOT NULL DEFAULT '0',
  `stat_value1` int(10) NOT NULL DEFAULT '0',
  `stat_type2` int(10) NOT NULL DEFAULT '0',
  `stat_value2` int(10) NOT NULL DEFAULT '0',
  `stat_type3` int(10) NOT NULL DEFAULT '0',
  `stat_value3` int(10) NOT NULL DEFAULT '0',
  `stat_type4` int(10) NOT NULL DEFAULT '0',
  `stat_value4` int(10) NOT NULL DEFAULT '0',
  `delay` smallint(5) unsigned NOT NULL DEFAULT '1000',
  `description` varchar(255) NOT NULL DEFAULT '',
  `itemset` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `Durability` smallint(5) unsigned NOT NULL DEFAULT '0',
  `MaxDurability` smallint(5) unsigned NOT NULL DEFAULT '0',
  `FoodType` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `icon` varchar(255) NOT NULL DEFAULT '',
  `mesh` varchar(255) NOT NULL DEFAULT '',
  PRIMARY KEY (`ID`,`""`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED COMMENT='Item System';

-- ----------------------------
-- Table structure for maps
-- ----------------------------
DROP TABLE IF EXISTS `maps`;
CREATE TABLE `maps` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `Name` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=0 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for pendingrequest
-- ----------------------------
DROP TABLE IF EXISTS `pendingrequest`;
CREATE TABLE `pendingrequest` (
  `ID` int(10) NOT NULL AUTO_INCREMENT,
  `fromWho` varchar(20) DEFAULT NULL,
  `toWho` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Table structure for realmd
-- ----------------------------
DROP TABLE IF EXISTS `realmd`;
CREATE TABLE `realmd` (
  `realmdID` int(10) NOT NULL AUTO_INCREMENT,
  `servername` varchar(20) DEFAULT NULL,
  `ip` varchar(100) DEFAULT NULL,
  `port` varchar(100) DEFAULT NULL,
  `onlinePlayer` int(10) DEFAULT '0',
  `online` smallint(1) DEFAULT '0',
  PRIMARY KEY (`realmdID`)
) ENGINE=InnoDB AUTO_INCREMENT=0 DEFAULT CHARSET=latin1;
