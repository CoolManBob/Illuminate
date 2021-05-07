DROP TABLE IF EXISTS `account`;
CREATE TABLE `account` (
  `_id` int NOT NULL AUTO_INCREMENT,
  `accountName` varchar(45) DEFAULT NULL,
  `email` varchar(64) DEFAULT NULL,
  `password` varchar(64) DEFAULT NULL,
  `pin` int(8) DEFAULT 1,
  `accessLvl` int(8) DEFAULT 1,
  `confirmationHash` varchar(128) DEFAULT NULL,
  `changPasswordHash` varchar(128) DEFAULT NULL,
  `registrationData` varchar(64) DEFAULT NULL,
  `host` float(32) DEFAULT NULL,
  PRIMARY KEY (`_id`),
  UNIQUE KEY `name_UNIQUE` (`accountName`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;illuminatelogin_illuminatelogin