create database if not exists blog_system;

use blog_system;

create table if not exists table_tag(
    id int primary key auto_increment,
    name varchar(32) unique comment"用户名称"
);
create table if not exists table_user (id int primary key auto_increment,name varchar(32) comment "标签名称",unique key (name));

create table if not exists table_blog (
    id int primary key auto_increment comment "博客ID",
    tag_id int comment "所属标签ID",
    user_id int comment "所属用户ID",
    title varchar(255) comment "博客标题",
    content text comment "博客正文",
    ctime datetime comment "博客最后改变时间",
    foreign key (tag_id) references table_tag(id),
    foreign key (user_id) references table_user(id)
);
