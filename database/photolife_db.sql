BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS "Medicine" (
	"id"	INTEGER,
	"name"	TEXT,
	"photo"	BLOB,
	"descripriom"	TEXT,
	"effects"	TEXT,
	PRIMARY KEY("id")
);
CREATE TABLE IF NOT EXISTS "patient" (
	"id"	INTEGER,
	"fullname"	TEXT,
	"gender"	TEXT,
	"date_birth"	TEXT,
	"address"	TEXT,
	PRIMARY KEY("id")
);
CREATE TABLE IF NOT EXISTS "authoriz" (
	"login"	text(128) NOT NULL,
	"password"	text(128) NOT NULL,
	"id"	INTEGER,
	"fullname"	text(128),
	PRIMARY KEY("id")
);
CREATE TABLE IF NOT EXISTS "calls" (
	"id"	INTEGER,
	"patient_name"	TEXT,
	"doctor_name"	TEXT,
	"date"	TEXT,
	"address"	TEXT,
	"symptoms"	TEXT,
	"diagnosis"	TEXT,
	"prescription"	TEXT,
	"medecine_id"	TEXT,
	PRIMARY KEY("id")
);
COMMIT;
