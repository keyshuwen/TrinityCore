-- ----------------------------
-- Table _ace_account_extra
-- ----------------------------
ALTER TABLE _ace_account_extra ADD viplevel int(10) NOT NULL DEFAULT '0' AFTER id; 

-- ----------------------------
-- Table rbac_permissions
-- ---------------------------- 
INSERT INTO rbac_permissions (id, name) VALUES (3004, 'Command: ace reLoad vipSystem');
INSERT INTO rbac_permissions (id, name) VALUES (3005, 'Command: ace vip');

-- ----------------------------
-- Table rbac_linked_permissions
-- ---------------------------- 
INSERT INTO rbac_linked_permissions (id, linkedId) VALUES (194, 3004);
INSERT INTO rbac_linked_permissions (id, linkedId) VALUES (194, 3005);
