-- ----------------------------
-- Table rbac_permissions
-- ---------------------------- 
INSERT INTO rbac_permissions VALUES (3000, 'Command: ace');
INSERT INTO rbac_permissions VALUES (3001, 'Command: ace reLoad');
INSERT INTO rbac_permissions VALUES (3002, 'Command: ace reLoad aceConfig');

-- ----------------------------
-- Table rbac_linked_permissions
-- ---------------------------- 
INSERT INTO rbac_linked_permissions VALUES (194, 3000);
INSERT INTO rbac_linked_permissions VALUES (194, 3001);
INSERT INTO rbac_linked_permissions VALUES (194, 3002);
