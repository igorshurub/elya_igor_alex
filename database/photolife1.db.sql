BEGIN TRANSACTION;
CREATE TABLE "patient" (
	"id"	INTEGER,
	"fullname"	TEXT,
	"gender"	TEXT,
	"date_birth"	TEXT,
	"address"	TEXT,
	PRIMARY KEY("id")
);
CREATE TABLE "authorization" (
	"login"	text(128) NOT NULL,
	"password"	text(128) NOT NULL,
	"id"	INTEGER,
	"fullname"	text(128),
	PRIMARY KEY("id")
);
CREATE TABLE "calls" (
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
CREATE TABLE "Medicine" (
	"id"	INTEGER,
	"name"	TEXT,
	"descripriom"	TEXT,
	"effects"	TEXT,
	PRIMARY KEY("id")
);
INSERT INTO "patient" ("id","fullname","gender","date_birth","address") VALUES (1,'Игорь Шуруб','муж','2002-01-02','ул Московских пионеров д 44 к 1');
INSERT INTO "authorization" ("login","password","id","fullname") VALUES ('ivan','Qwerty123!',1,'Иваныч'),('fedor','Asdfg123!',2,'Феодосиф');
INSERT INTO "calls" ("id","patient_name","doctor_name","date","address","symptoms","diagnosis","prescription","medecine_id") VALUES (1,'Шуруб И.С.','Иванов Иван','2022-02-02','Ул Кукушкина д 69 к2','Головная боль, температура','Грипп','Соблюдать домашний режим','Ингавирин'),(2,'Алексей Самсонов','Иванов Иван','2022-02-01','Ул Космонавтов д 43','Рвота','Отравление','Пить смекту','Смекта');
INSERT INTO "Medicine" ("id","name","descripriom","effects") VALUES (1,'Ингавирин','Ингавирин® снижает вирусную нагрузку, ускоряет элиминацию вирусов, сокращает продолжительность болезни, снижает риск развития осложнений. Механизм действия реализуется на уровне инфицированных клеток за счет активации факторов врожденного иммунитета, подавляемых вирусными белками','К основным противопоказаниям стоит отнести: индивидуальную непереносимость; период беременности и лактации; нехватку или непереносимость лактазы; глюкозо-галактозную мальабсорбацию; серьезные нарушения в функционировании почек и печени.'),(2,'Ношпа','Форма выпуска, упаковка и состав препарата Но-шпа Таблетки желтого с зеленоватым или оранжеватым оттенком цвета, круглые, двояковыпуклые, с гравировкой "spa" на одной стороне. 1 таб. Вспомогательные вещества: магния стеарат - 3 мг, тальк - 4 мг, повидон - 6 мг, крахмал кукурузный - 35 мг, лактозы моногидрат - 52 мг.','Со стороны нервной системы: редко – головная боль, вертиго, бессонница; частота неизвестна - головокружение. Со стороны сердечно-сосудистой системы: редко – ощущение сердцебиения, снижение АД. Со стороны ЖКТ: редко – тошнота, запор.'),(3,'Смекта','От рвоты','Головокружение');
COMMIT;
