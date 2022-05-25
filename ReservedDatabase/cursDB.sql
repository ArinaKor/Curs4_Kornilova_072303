/*
Navicat MySQL Data Transfer

Source Server         : mycurs
Source Server Version : 80028
Source Host           : localhost:3306
Source Database       : curs

Target Server Type    : MYSQL
Target Server Version : 80028
File Encoding         : 65001

Date: 2022-05-23 12:14:34
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for `company`
-- ----------------------------
DROP TABLE IF EXISTS `company`;
CREATE TABLE `company` (
  `company_id` int NOT NULL AUTO_INCREMENT,
  `company_name` varchar(15) CHARACTER SET cp1251 COLLATE cp1251_general_ci NOT NULL,
  `activity` varchar(40) CHARACTER SET cp1251 COLLATE cp1251_general_ci DEFAULT NULL,
  `finance` int DEFAULT '0',
  PRIMARY KEY (`company_id`) USING BTREE,
  UNIQUE KEY `company_name` (`company_name`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=cp1251 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Table structure for `mark`
-- ----------------------------
DROP TABLE IF EXISTS `mark`;
CREATE TABLE `mark` (
  `mark_id` int NOT NULL AUTO_INCREMENT,
  `number` int DEFAULT NULL,
  `user_id` int DEFAULT NULL,
  `project1_id` int DEFAULT NULL,
  `project2_id` int DEFAULT NULL,
  `mark1` float DEFAULT NULL,
  `mark2` float DEFAULT NULL,
  UNIQUE KEY `mark_id` (`mark_id`) USING BTREE,
  KEY `users_id` (`user_id`) USING BTREE,
  KEY `project1_id` (`project1_id`) USING BTREE,
  KEY `project2_id` (`project2_id`) USING BTREE,
  CONSTRAINT `mark_ibfk_1` FOREIGN KEY (`user_id`) REFERENCES `user` (`user_id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `mark_ibfk_2` FOREIGN KEY (`project1_id`) REFERENCES `project` (`project_id`) ON DELETE RESTRICT ON UPDATE RESTRICT,
  CONSTRAINT `mark_ibfk_3` FOREIGN KEY (`project2_id`) REFERENCES `project` (`project_id`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE=InnoDB AUTO_INCREMENT=31 DEFAULT CHARSET=cp1251 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Table structure for `project`
-- ----------------------------
DROP TABLE IF EXISTS `project`;
CREATE TABLE `project` (
  `project_id` int NOT NULL AUTO_INCREMENT,
  `project_name` varchar(50) CHARACTER SET cp1251 COLLATE cp1251_general_ci NOT NULL,
  `sum_credit` decimal(12,3) NOT NULL,
  `credit_time` int NOT NULL,
  `sud_reestr` varchar(3) CHARACTER SET cp1251 COLLATE cp1251_general_ci NOT NULL DEFAULT 'Нет',
  `application_date` date NOT NULL,
  `company_id` int DEFAULT NULL,
  PRIMARY KEY (`project_id`) USING BTREE,
  KEY `Project_fk1` (`company_id`) USING BTREE,
  CONSTRAINT `Project_fk1` FOREIGN KEY (`company_id`) REFERENCES `company` (`company_id`) ON DELETE RESTRICT ON UPDATE RESTRICT
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=cp1251 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Table structure for `user`
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user` (
  `user_id` int NOT NULL AUTO_INCREMENT,
  `user_name` varchar(50) CHARACTER SET cp1251 COLLATE cp1251_general_ci NOT NULL,
  `login` varchar(40) CHARACTER SET cp1251 COLLATE cp1251_general_ci NOT NULL,
  `pass` varchar(40) CHARACTER SET cp1251 COLLATE cp1251_general_ci NOT NULL,
  `role` varchar(40) CHARACTER SET cp1251 COLLATE cp1251_general_ci DEFAULT NULL,
  PRIMARY KEY (`user_id`) USING BTREE,
  UNIQUE KEY `login` (`login`) USING BTREE,
  KEY `role` (`role`) USING BTREE,
  KEY `pass` (`pass`) USING BTREE,
  KEY `user_name` (`user_name`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=22 DEFAULT CHARSET=cp1251 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of user
-- ----------------------------
INSERT INTO `user` VALUES ('1', 'Arina', 'Arina', '1601', 'Менеджер');

-- ----------------------------
-- Table structure for `user_role`
-- ----------------------------
DROP TABLE IF EXISTS `user_role`;
CREATE TABLE `user_role` (
  `name` varchar(40) CHARACTER SET cp1251 COLLATE cp1251_general_ci NOT NULL,
  PRIMARY KEY (`name`),
  UNIQUE KEY `name` (`name`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=cp1251 ROW_FORMAT=DYNAMIC;

-- ----------------------------
-- Records of user_role
-- ----------------------------
INSERT INTO `user_role` VALUES ('Администратор');
INSERT INTO `user_role` VALUES ('Консультант банка');
INSERT INTO `user_role` VALUES ('Эксперт');
