# Ticket Point
  ![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white) ![MySQL](https://img.shields.io/badge/mysql-%2300f.svg?style=for-the-badge&logo=mysql&logoColor=white)
  ![Github Version](https://img.shields.io/badge/version-0.0.2-red) ![Status](https://img.shields.io/badge/status-prototype-red)
  ![License](https://img.shields.io/badge/license-GPL--3.0-blue) ![System](https://img.shields.io/badge/system-Linux-blue) ![CMake](https://img.shields.io/badge/CMake-3.16.3-blue)
  ![Build](https://img.shields.io/badge/build-passing-brightgreen)
  
## Overview
Ticket Point is a trouble ticketing platform.
The platform allows the user to report a problem in the form of a ticket.
Technicians receive tickets and provide proper solutions.

## Configuration
1. Create schema:
```sql
    CREATE DATABASE IF NOT EXISTS TicketPoint_DB;
``` 
2. Create tables:
```sql
CREATE TABLE IF NOT EXISTS Skill (
  skillId INT PRIMARY KEY,
  title VARCHAR(30) NOT NULL
);

CREATE TABLE IF NOT EXISTS Status (
  statusCode INT PRIMARY KEY,
  statusMessagge VARCHAR(30) NOT NULL
);

CREATE TABLE IF NOT EXISTS User (
  UserId INT PRIMARY KEY,
  mail VARCHAR(50) NOT NULL,
  name VARCHAR(30) NOT NULL,
  lastname VARCHAR(30) NOT NULL,
  password VARCHAR(30) NOT NULL,
  skillId INT DEFAULT 0,
  isTechnician TINYINT(1) DEFAULT 0,
  FOREIGN KEY (skillId) REFERENCES Skill(skillId)
);

CREATE TABLE IF NOT EXISTS Ticket (
  ticketId INT PRIMARY KEY,
  problemText VARCHAR(100) NOT NULL,
  openingDate DATE NOT NULL,
  closingDate DATE,
  statusCode INT NOT NULL,
  userId INT NOT NULL,
  technicianID INT,
  FOREIGN KEY (statusCode) REFERENCES Status(statusCode),
  FOREIGN KEY (userId) REFERENCES User(userId),
  FOREIGN KEY (technicianId) REFERENCES User(userId)
);
``` 
3. Create user:
```sql
    CREATE USER 'ticketpoint_user'@'localhost' IDENTIFIED WITH mysql_native_password BY 'T!cketPo1ntPassword';
```
4. Grant privileges:
```sql
GRANT SELECT, INSERT ON TicketPoint_DB.User TO 'ticketpoint_user'@'localhost';
GRANT SELECT, INSERT ON TicketPoint_DB.Ticket TO 'ticketpoint_user'@'localhost';
``` 

## License
GNU GPL 3.0