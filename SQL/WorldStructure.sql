DROP TABLE IF EXISTS `creature_template`;
CREATE TABLE `creature_template`
(
    `entry` INT UNSIGNED NOT NULL AUTO_INCREMENT,
    `name` CHAR(192) NOT NULL,
    `tileset` VARCHAR(20) NOT NULL,
    `texture_x` SMALLINT UNSIGNED NOT NULL,
    `texture_y` SMALLINT UNSIGNED NOT NULL,
    `npcflag` SMALLINT UNSIGNED NOT NULL,
    `maxhealth` INT UNSIGNED NOT NULL,
    `maxpower` INT UNSIGNED NOT NULL,
    `ScriptName` CHAR(192),
    PRIMARY KEY(entry)
);

DROP TABLE IF EXISTS `gameobject_template`;
CREATE TABLE `gameobject_template`
(
    `entry` INT UNSIGNED NOT NULL AUTO_INCREMENT,
    `name` CHAR(192) NOT NULL,
    `tileset` VARCHAR(20) NOT NULL,
    `texture_x` SMALLINT UNSIGNED NOT NULL,
    `texture_y` SMALLINT UNSIGNED NOT NULL,
    `goflag` SMALLINT UNSIGNED NOT NULL,
    `ScriptName` CHAR(192),
    PRIMARY KEY(entry)
);

DROP TABLE IF EXISTS `spell_template`;
CREATE TABLE `spell_template`
(
    `entry` INT UNSIGNED NOT NULL AUTO_INCREMENT,
    `name` CHAR(192) NOT NULL,
    `tileset` VARCHAR(20) NOT NULL,
    `texture_x` SMALLINT UNSIGNED NOT NULL,
    `texture_y` SMALLINT UNSIGNED NOT NULL,
    `spellflag` SMALLINT UNSIGNED NOT NULL,
    `base_value` INT UNSIGNED NOT NULL,
    `base_cost` INT UNSIGNED NOT NULL,
    PRIMARY KEY(entry)
);

DROP TABLE IF EXISTS `item_template`;
CREATE TABLE `item_template`
(
    `entry` INT UNSIGNED NOT NULL AUTO_INCREMENT,
    `name` CHAR(192) NOT NULL,
    `class` SMALLINT UNSIGNED NOT NULL,
    `tileset` VARCHAR(20) NOT NULL,
    `texture_x` SMALLINT UNSIGNED NOT NULL,
    `texture_y` SMALLINT UNSIGNED NOT NULL,
    `inventory_type` INT UNSIGNED NOT NULL,
    `container_slots` SMALLINT UNSIGNED,
    `description` TEXT NOT NULL,
    PRIMARY KEY(entry)
);

DROP TABLE IF EXISTS `map_template`;
CREATE TABLE `map_template`
(
    `entry` INT UNSIGNED NOT NULL AUTO_INCREMENT,
    `name` CHAR(192) NOT NULL,
    `size_x` TINYINT UNSIGNED NOT NULL,
    `size_y` TINYINT UNSIGNED NOT NULL,
    `mapflag` TINYINT UNSIGNED NOT NULL,
    `ScriptName` CHAR(192),
    PRIMARY KEY(entry)
);

DROP TABLE IF EXISTS `quest_template`;
CREATE TABLE `quest_template`
(
    `entry` INT UNSIGNED NOT NULL AUTO_INCREMENT,
    `title` CHAR(192) NOT NULL,
    `details` TEXT,
    `objective` CHAR(192) NOT NULL,
    PRIMARY KEY(entry)
);

DROP TABLE IF EXISTS `creature_quest`;
CREATE TABLE `creature_quest`
(
    `creature_entry` INT UNSIGNED NOT NULL,
    `quest_entry` INT UNSIGNED NOT NULL
);

DROP TABLE IF EXISTS `player_template`;
CREATE TABLE `player_template`
(
    `entry` INT UNSIGNED NOT NULL AUTO_INCREMENT,
    `class` CHAR(192) NOT NULL,
    `tileset` VARCHAR(20) NOT NULL,
    `texture_x` SMALLINT UNSIGNED NOT NULL,
    `texture_y` SMALLINT UNSIGNED NOT NULL,
    PRIMARY KEY(entry)
);

DROP TABLE IF EXISTS `creature`;
CREATE TABLE `creature`
(
    `guid` BIGINT UNSIGNED NOT NULL,
    `entry` INT UNSIGNED NOT NULL,
    `map_guid` INT UNSIGNED NOT NULL,
    `x` TINYINT UNSIGNED NOT NULL,
    `y` TINYINT UNSIGNED NOT NULL,
    PRIMARY KEY(guid)
);

DROP TABLE IF EXISTS `gameobject`;
CREATE TABLE `gameobject`
(
    `guid` BIGINT UNSIGNED NOT NULL,
    `entry` INT UNSIGNED NOT NULL,
    `map_guid` INT UNSIGNED NOT NULL,
    `x` TINYINT UNSIGNED NOT NULL,
    `y` TINYINT UNSIGNED NOT NULL,
    PRIMARY KEY(guid)
);

DROP TABLE IF EXISTS `map`;
CREATE TABLE `map`
(
    `guid` BIGINT UNSIGNED NOT NULL,
    `size_x` TINYINT UNSIGNED NOT NULL,
    `size_y` TINYINT UNSIGNED NOT NULL,
    PRIMARY KEY(guid)
);
