SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for _ace_account_extra
-- ----------------------------
DROP TABLE IF EXISTS `_ace_account_extra`;
CREATE TABLE `_ace_account_extra`  (
  `id` int(10) UNSIGNED NOT NULL DEFAULT 0,
  `jf` int(10) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

SET FOREIGN_KEY_CHECKS = 1;

-- ----------------------------
-- Table rbac_permissions
-- ---------------------------- 
INSERT INTO rbac_permissions (id, name) VALUES (3003, 'Command: ace jf');

-- ----------------------------
-- Table rbac_linked_permissions
-- ---------------------------- 
INSERT INTO rbac_linked_permissions (id, linkedId) VALUES (194, 3003);
