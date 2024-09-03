DROP DATABASE IF EXISTS db_esproject_door;

CREATE DATABASE db_esproject_door COLLATE utf8mb4_general_ci;

use db_esproject_door;

DROP TABLE IF EXISTS tb_user;

CREATE TABLE tb_user(
	id INTEGER NOT NULL PRIMARY KEY AUTO_INCREMENT,
	name VARCHAR(50) NOT NULL,
    password VARCHAR(128) NOT NULL
);

INSERT INTO tb_user(name, password) VALUES("OWNER", "00c9e8bf30e5c8980d5a70bb336f892c7c23a47f316a6054c9041e677d35e66aab72cabb9eb2a858a7a6f4cc55cb2cff0de1387968ea09528759e017f0ab5ce3");
INSERT INTO tb_user(name, password) VALUES("akarui", "00c9e8bf30e5c8980d5a70bb336f892c7c23a47f316a6054c9041e677d35e66aab72cabb9eb2a858a7a6f4cc55cb2cff0de1387968ea09528759e017f0ab5ce3");