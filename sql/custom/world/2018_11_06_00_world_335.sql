SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for _ace_config
-- ----------------------------
DROP TABLE IF EXISTS `_ace_config`;
CREATE TABLE `_ace_config`  (
  `entry` varchar(60) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `value` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `cost` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `Comment` text CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`entry`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of _ace_config
-- ----------------------------
INSERT INTO _ace_config VALUES ('Player.login', 0, 0, '【登录提示】value：是否开启 0=关闭  1=开启');

SET FOREIGN_KEY_CHECKS = 1;

-- ----------------------------
-- Table trinity_string 
-- ---------------------------- 
INSERT INTO trinity_string VALUES (90000, 'Welcome new people [%s] to World of Warcraft.', NULL, NULL, NULL, '欢迎新人[%s]来到魔兽世界.', NULL, NULL, NULL, NULL);
INSERT INTO trinity_string VALUES (90001, '[%s]: Set foot on the journey again!', NULL, NULL, NULL, '[%s]: 再次踏上征程!', NULL, NULL, NULL, NULL);
