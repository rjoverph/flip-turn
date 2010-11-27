##
##  Create the Database
##
##  Change password and username(s) as necessary.
##
create database flip-turn ;
use flip-turn ;
create table flip-turn (flip-turn varchar(50)) ;
grant all on flip-turn.* to flip-turn identified by 'flip-turn' ;
grant all on flip-turn.* to flip-turn@localhost identified by 'flip-turn' ;
SET PASSWORD FOR flip-turn@localhost = OLD_PASSWORD('flip-turn')

##  Create the swimmer database
CREATE TABLE `results` (
	`resultid` INT(10) NOT NULL AUTO_INCREMENT,
	`event` SMALLINT(6) NULL DEFAULT '0',
	`course` TINYINT(4) NULL DEFAULT '0',
	`stroke` SMALLINT(6) NULL DEFAULT '0',
	`distance` SMALLINT(6) NULL DEFAULT '0',
	`swimtime` FLOAT NULL DEFAULT '0',
	`heat` SMALLINT(6) NULL DEFAULT '0',
	`lane` SMALLINT(6) NULL DEFAULT '0',
	`place` SMALLINT(6) NULL DEFAULT '0',
	`date` DATE NULL DEFAULT NULL,
	INDEX `resultid` (`resultid`)
)
COLLATE='utf8_general_ci'
ENGINE=InnoDB
ROW_FORMAT=DEFAULT

##  Create the results database
CREATE TABLE `swimmer` (
	`swimmerid` INT(10) NOT NULL AUTO_INCREMENT,
	`lastname` TEXT NULL,
	`firstname` TEXT NULL,
	`middle` TEXT NULL,
	`dob` DATE NULL DEFAULT NULL,
	`uss` TEXT NULL,
	`gender` TINYINT(4) NULL DEFAULT NULL,
	INDEX `swimmerid` (`swimmerid`)
)
COLLATE='utf8_general_ci'
ENGINE=InnoDB
ROW_FORMAT=DEFAULT

