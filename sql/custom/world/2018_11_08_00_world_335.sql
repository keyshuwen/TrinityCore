SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for _ace_vip_system
-- ----------------------------
DROP TABLE IF EXISTS `_ace_vip_system`;
CREATE TABLE `_ace_vip_system`  (
  `entry` int(10) UNSIGNED NOT NULL,
  `title` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `nameColor` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `chatColor` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `reqItem` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `jfCost` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `everyDayItem` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `addAutojf` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `lootRate` float UNSIGNED NOT NULL DEFAULT 0,
  `HealthRate` float UNSIGNED NOT NULL DEFAULT 0,
  `dmgRate` float UNSIGNED NOT NULL DEFAULT 0,
  `cureRate` float UNSIGNED NOT NULL DEFAULT 0,
  `xpRate` float UNSIGNED NOT NULL DEFAULT 0,
  `reputationRate` float UNSIGNED NOT NULL DEFAULT 0,
  `adduppro` float UNSIGNED NOT NULL DEFAULT 0,
  `aura` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `talent` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `description` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  PRIMARY KEY (`entry`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

SET FOREIGN_KEY_CHECKS = 1;

-- ----------------------------
-- Table _ace_config
-- ----------------------------
UPDATE _ace_config SET Comment = '【登录提示】value：是否开启 0=关闭  1=开启新人提示 2=开启老人提示 3=开启全部提示\n cost：0=名字显示前缀前面 1=名字显示前缀后面' WHERE entry = 'Player.login';
INSERT INTO _ace_config VALUES ('Player.vipSystem', 0, 0, '【VIP 功能】value：是否开启 0=关闭  1=开启');

-- ----------------------------
-- Table command 
-- ---------------------------- 
INSERT INTO command VALUES ('ace reLoad vipSystem', 3004, 'Syntax: .ace reLoad vipSystem');
INSERT INTO command VALUES ('ace vip', 3005, 'Syntax: .ace vip');

-- ----------------------------
-- Table trinity_string 
-- ---------------------------- 
DELETE FROM trinity_string WHERE entry IN (90000,90001,90003);

INSERT INTO trinity_string VALUES (90000, '|TInterface\\COMMON\\VOICECHAT-SPEAKER:18:18:4:-3|tWelcome new people [%s%s] to World of Warcraft, Race belongs to %s, Cheers for him!', NULL, NULL, NULL, '|TInterface\\COMMON\\VOICECHAT-SPEAKER:18:18:4:-3|t欢迎新人[%s%s]来到魔兽世界, 种族属于%s, 为他欢呼!', NULL, NULL, NULL, NULL);
INSERT INTO trinity_string VALUES (90001, '|TInterface\\COMMON\\VOICECHAT-SPEAKER:18:18:4:-3|t[%s%s]: Set foot on the journey again, in order to %s!', NULL, NULL, NULL, '|TInterface\\COMMON\\VOICECHAT-SPEAKER:18:18:4:-3|t[%s%s]: 再次踏上征程, 为了%s!', NULL, NULL, NULL, NULL);
INSERT INTO trinity_string VALUES (90003, 'Changing VIP level, [%s] The current VIP level is set to %u.', NULL, NULL, NULL, '改变VIP等级, [%s]当前VIP等级设置为%u.', NULL, NULL, NULL, NULL);
