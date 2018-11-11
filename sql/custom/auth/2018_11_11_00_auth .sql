-- ----------------------------
-- Table rbac_permissions
-- ---------------------------- 
INSERT INTO rbac_permissions (id, name) VALUES (3006, 'Command: sj');
INSERT INTO rbac_permissions (id, name) VALUES (3007, 'Command: zy');

-- ----------------------------
-- Table rbac_linked_permissions
-- ---------------------------- 
INSERT INTO rbac_linked_permissions (id, linkedId) VALUES (195, 3006);
INSERT INTO rbac_linked_permissions (id, linkedId) VALUES (195, 3007);