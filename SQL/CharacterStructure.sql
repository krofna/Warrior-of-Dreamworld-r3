DROP TABLE IF EXISTS `players`;
CREATE TABLE `players`
(
    `guid` BIGINT UNSIGNED NOT NULL,
    `username` VARCHAR(20) NOT NULL,
    `hash` VARCHAR(255) NOT NULL,
    `email` VARCHAR(40) NOT NULL,
    `online` TINYINT UNSIGNED DEFAULT 0,
    `seclevel` TINYINT UNSIGNED DEFAULT 0,
    `tileset` VARCHAR(20) NOT NULL,
    `tx` SMALLINT UNSIGNED NOT NULL,
    `ty` SMALLINT UNSIGNED NOT NULL,
    `mapid` SMALLINT UNSIGNED NOT NULL,
    `x` SMALLINT UNSIGNED NOT NULL,
    `y` SMALLINT UNSIGNED NOT NULL,
    PRIMARY KEY(guid)
);