CREATE DATABASE  IF NOT EXISTS `homer` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE `homer`;
-- MySQL dump 10.13  Distrib 5.6.17, for Win64 (x86_64)
--
-- Host: localhost    Database: homer
-- ------------------------------------------------------
-- Server version	5.5.41-0+wheezy1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `Colors`
--

DROP TABLE IF EXISTS `Colors`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Colors` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(45) NOT NULL,
  `red` int(11) NOT NULL,
  `green` int(11) NOT NULL,
  `blue` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name_UNIQUE` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Colors`
--

LOCK TABLES `Colors` WRITE;
/*!40000 ALTER TABLE `Colors` DISABLE KEYS */;
INSERT INTO `Colors` VALUES (1,'red',255,0,0),(2,'green',0,255,0),(3,'blue',0,0,255),(4,'orange',83,4,0),(5,'yellow',255,255,0),(6,'indigo',4,0,19),(7,'violet',23,0,22),(8,'cyan',0,255,255),(9,'magenta',255,0,255),(10,'white',255,255,255),(11,'black',0,0,0),(12,'pink',158,4,79);
/*!40000 ALTER TABLE `Colors` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Event_Log`
--

DROP TABLE IF EXISTS `Event_Log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Event_Log` (
  `LID` int(11) NOT NULL AUTO_INCREMENT,
  `Date` datetime NOT NULL,
  `Type` varchar(45) NOT NULL,
  `Message` text NOT NULL,
  PRIMARY KEY (`LID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Event_Log`
--

LOCK TABLES `Event_Log` WRITE;
/*!40000 ALTER TABLE `Event_Log` DISABLE KEYS */;
/*!40000 ALTER TABLE `Event_Log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Nodes`
--

DROP TABLE IF EXISTS `Nodes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Nodes` (
  `NodeID` int(11) NOT NULL AUTO_INCREMENT,
  `IP` varchar(15) NOT NULL,
  `MAC` varchar(17) NOT NULL,
  `Loc` varchar(60) NOT NULL,
  `Sensors` text CHARACTER SET utf8 NOT NULL,
  PRIMARY KEY (`NodeID`),
  UNIQUE KEY `IP_UNIQUE` (`IP`),
  UNIQUE KEY `MAC_UNIQUE` (`MAC`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Nodes`
--

LOCK TABLES `Nodes` WRITE;
/*!40000 ALTER TABLE `Nodes` DISABLE KEYS */;
/*!40000 ALTER TABLE `Nodes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Sensor_Log`
--

DROP TABLE IF EXISTS `Sensor_Log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Sensor_Log` (
  `LID` int(11) NOT NULL AUTO_INCREMENT,
  `Date` datetime NOT NULL,
  `NodeID` int(11) NOT NULL,
  `Data` text CHARACTER SET utf8 NOT NULL COMMENT 'JSON\nextTemp: double\nintTemp: double\nlight: double\ncarmon: double\nmotion: boolean',
  PRIMARY KEY (`LID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Sensor_Log`
--

LOCK TABLES `Sensor_Log` WRITE;
/*!40000 ALTER TABLE `Sensor_Log` DISABLE KEYS */;
/*!40000 ALTER TABLE `Sensor_Log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Settings`
--

DROP TABLE IF EXISTS `Settings`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Settings` (
  `PID` int(11) NOT NULL AUTO_INCREMENT,
  `Date_Updated` datetime NOT NULL,
  `User` varchar(45) NOT NULL,
  `Settings` text NOT NULL COMMENT 'JSON\ndesired_temp: int\nrestricted_time_start: Time\nrestricted_time_end: Time\ndebug_display: boolean\nr1: boolean\nr2: boolean\nr3: boolean\nr4: boolean\nr5: boolean\nr6: boolean',
  PRIMARY KEY (`PID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Settings`
--

LOCK TABLES `Settings` WRITE;
/*!40000 ALTER TABLE `Settings` DISABLE KEYS */;
/*!40000 ALTER TABLE `Settings` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ctrl_surf`
--

DROP TABLE IF EXISTS `ctrl_surf`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ctrl_surf` (
  `PID` int(11) NOT NULL AUTO_INCREMENT,
  `Type` varchar(45) NOT NULL,
  `Loc` varchar(60) NOT NULL,
  `State` varchar(45) NOT NULL,
  PRIMARY KEY (`PID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ctrl_surf`
--

LOCK TABLES `ctrl_surf` WRITE;
/*!40000 ALTER TABLE `ctrl_surf` DISABLE KEYS */;
/*!40000 ALTER TABLE `ctrl_surf` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2015-02-09 15:45:20
