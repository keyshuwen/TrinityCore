-- ----------------------------
-- Table _ace_config
-- ----------------------------
INSERT INTO _ace_config VALUES ('Player.world.chat', 0, 0, '【世界聊天】value：\n 0=关闭 \n 1=开启(名字显示前缀前面) cost=消耗的金币数量 \n 2=开启(名字显示前缀前面) cost=消耗的积分数量\n 3=开启(名字显示前缀前面) cost=消耗的物品ID \n 4=开启(名字显示前缀后面) cost=消耗的金币数量 \n 5=开启(名字显示前缀后面) cost=消耗的积分数量\n 6=开启(名字显示前缀后面) cost=消耗的物品ID');
INSERT INTO _ace_config VALUES ('Player.world.Facttion.chat', 0, 0, '【阵营聊天】value：\n 0=关闭 \n 1=开启(名字显示前缀前面) cost=消耗的金币数量 \n 2=开启(名字显示前缀前面) cost=消耗的积分数量\n 3=开启(名字显示前缀前面) cost=消耗的物品ID \n 4=开启(名字显示前缀后面) cost=消耗的金币数量 \n 5=开启(名字显示前缀后面) cost=消耗的积分数量\n 6=开启(名字显示前缀后面) cost=消耗的物品ID');

-- ----------------------------
-- Table command 
-- ---------------------------- 
INSERT INTO command VALUES ('sj', 3006, 'Syntax: .sj or Lack of cost');
INSERT INTO command VALUES ('zy', 3007, 'Syntax: .zy or Lack of cost');

-- ----------------------------
-- Table trinity_string 
-- ---------------------------- 
DELETE FROM trinity_string WHERE entry IN (90004, 90005, 90006, 90007, 90008);

INSERT INTO trinity_string VALUES (90004, '[WorldChat]%s[%s%s]: %s', NULL, NULL, NULL, '[世界频道]%s[%s%s]: %s', NULL, NULL, NULL, NULL);
INSERT INTO trinity_string VALUES (90005, '|cFF00CCCC[FacttionChat]|r%s[%s%s]: %s', NULL, NULL, NULL, '|cFF00CCCC[阵营频道]|r%s[%s%s]: %s', NULL, NULL, NULL, NULL);
INSERT INTO trinity_string VALUES (90006, '|cFF33CCFFCongratulations! Your jf increased by %u points.|r', NULL, NULL, NULL, '|cFF33CCFF恭喜你! 你的积分增加%u点.|r', NULL, NULL, NULL, NULL);
INSERT INTO trinity_string VALUES (90007, '|cFF33CCFFYou spent jf %u points.|r', NULL, NULL, NULL, '|cFF33CCFF你花费了%u点积分.|r', NULL, NULL, NULL, NULL);
INSERT INTO trinity_string VALUES (90008, '|cFF33CCFFSorry, Your jf is not enough!|r', NULL, NULL, NULL, '|cFF33CCFF对不起, 你的积分不足!|r', NULL, NULL, NULL, NULL);
