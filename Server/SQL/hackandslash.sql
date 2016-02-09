/*
Navicat MySQL Data Transfer

Source Server         : home
Source Server Version : 50617
Source Host           : localhost:3306
Source Database       : hackandslash

Target Server Type    : MYSQL
Target Server Version : 50617
File Encoding         : 65001

Date: 2016-02-09 10:52:40
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `accounts`
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
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of accounts
-- ----------------------------
INSERT INTO `accounts` VALUES ('1', 'atidote', 'atidote', 'active', '0', null);
INSERT INTO `accounts` VALUES ('2', 'kevin', 'kevin', 'active', '0', null);
INSERT INTO `accounts` VALUES ('3', 'toto', 'toto', 'active', '0', null);

-- ----------------------------
-- Table structure for `characters`
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
-- Records of characters
-- ----------------------------

-- ----------------------------
-- Table structure for `experiance`
-- ----------------------------
DROP TABLE IF EXISTS `experiance`;
CREATE TABLE `experiance` (
  `ID` int(10) NOT NULL AUTO_INCREMENT,
  `Level` int(10) NOT NULL,
  `MaxExpInThisLevel` int(10) NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=51 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of experiance
-- ----------------------------
INSERT INTO `experiance` VALUES ('1', '1', '417');
INSERT INTO `experiance` VALUES ('2', '2', '887');
INSERT INTO `experiance` VALUES ('3', '3', '1437');
INSERT INTO `experiance` VALUES ('4', '4', '2067');
INSERT INTO `experiance` VALUES ('5', '5', '2777');
INSERT INTO `experiance` VALUES ('6', '6', '3567');
INSERT INTO `experiance` VALUES ('7', '7', '4437');
INSERT INTO `experiance` VALUES ('8', '8', '5387');
INSERT INTO `experiance` VALUES ('9', '9', '6417');
INSERT INTO `experiance` VALUES ('10', '10', '7527');
INSERT INTO `experiance` VALUES ('11', '11', '8717');
INSERT INTO `experiance` VALUES ('12', '12', '9987');
INSERT INTO `experiance` VALUES ('13', '13', '11337');
INSERT INTO `experiance` VALUES ('14', '14', '12767');
INSERT INTO `experiance` VALUES ('15', '15', '14277');
INSERT INTO `experiance` VALUES ('16', '16', '15867');
INSERT INTO `experiance` VALUES ('17', '17', '17537');
INSERT INTO `experiance` VALUES ('18', '18', '19287');
INSERT INTO `experiance` VALUES ('19', '19', '21117');
INSERT INTO `experiance` VALUES ('20', '20', '23027');
INSERT INTO `experiance` VALUES ('21', '21', '25017');
INSERT INTO `experiance` VALUES ('22', '22', '27087');
INSERT INTO `experiance` VALUES ('23', '23', '29237');
INSERT INTO `experiance` VALUES ('24', '24', '29200');
INSERT INTO `experiance` VALUES ('25', '25', '31950');
INSERT INTO `experiance` VALUES ('26', '26', '34840');
INSERT INTO `experiance` VALUES ('27', '27', '37870');
INSERT INTO `experiance` VALUES ('28', '28', '41040');
INSERT INTO `experiance` VALUES ('29', '29', '44350');
INSERT INTO `experiance` VALUES ('30', '30', '47800');
INSERT INTO `experiance` VALUES ('31', '31', '51390');
INSERT INTO `experiance` VALUES ('32', '32', '55120');
INSERT INTO `experiance` VALUES ('33', '33', '58990');
INSERT INTO `experiance` VALUES ('34', '34', '63000');
INSERT INTO `experiance` VALUES ('35', '35', '67150');
INSERT INTO `experiance` VALUES ('36', '36', '71440');
INSERT INTO `experiance` VALUES ('37', '37', '75870');
INSERT INTO `experiance` VALUES ('38', '38', '80440');
INSERT INTO `experiance` VALUES ('39', '39', '85150');
INSERT INTO `experiance` VALUES ('40', '40', '90000');
INSERT INTO `experiance` VALUES ('41', '41', '94990');
INSERT INTO `experiance` VALUES ('42', '42', '100120');
INSERT INTO `experiance` VALUES ('43', '43', '105390');
INSERT INTO `experiance` VALUES ('44', '44', '110800');
INSERT INTO `experiance` VALUES ('45', '45', '116350');
INSERT INTO `experiance` VALUES ('46', '46', '122040');
INSERT INTO `experiance` VALUES ('47', '47', '127870');
INSERT INTO `experiance` VALUES ('48', '48', '133840');
INSERT INTO `experiance` VALUES ('49', '49', '139950');
INSERT INTO `experiance` VALUES ('50', '50', '146200');

-- ----------------------------
-- Table structure for `friendlist`
-- ----------------------------
DROP TABLE IF EXISTS `friendlist`;
CREATE TABLE `friendlist` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `account` varchar(20) DEFAULT NULL,
  `friend` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of friendlist
-- ----------------------------
INSERT INTO `friendlist` VALUES ('1', 'atidote', 'kevin');
INSERT INTO `friendlist` VALUES ('2', 'kevin', 'atidote');
INSERT INTO `friendlist` VALUES ('3', 'toto', 'atidote');
INSERT INTO `friendlist` VALUES ('4', 'atidote', 'toto');
INSERT INTO `friendlist` VALUES ('5', 'kevin', 'toto');
INSERT INTO `friendlist` VALUES ('6', 'toto', 'kevin');

-- ----------------------------
-- Table structure for `maps`
-- ----------------------------
DROP TABLE IF EXISTS `maps`;
CREATE TABLE `maps` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `Name` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of maps
-- ----------------------------
INSERT INTO `maps` VALUES ('0', 'TopDownExampleMap');
INSERT INTO `maps` VALUES ('1', 'ElevenRuins');

-- ----------------------------
-- Table structure for `realmd`
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
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of realmd
-- ----------------------------
INSERT INTO `realmd` VALUES ('1', 'France', '88.190.215.114', '30001', '0', '0');
INSERT INTO `realmd` VALUES ('2', 'English', '88.190.215.114', '7777', '0', '0');
