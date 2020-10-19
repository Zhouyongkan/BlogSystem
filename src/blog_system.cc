#include"db.hpp"
#include"httplib.h"
  
#define WWWROOT "./www"

blog_system::TableBlog *table_blog;
blog_system::TableTag *table_tag;
blog_system::TableUser *table_user;

void InsertUser(const httplib::Request &req,httplib::Response &rsp)
{
  //用户信息在req的body中
  //1.获取json字符串
  std::string json_str=req.body;

  //2.将json字符串解析为Json::Value对象
  Json::Reader reader;
  Json::Value root;
  bool ret=reader.parse(json_str,root);
  if(ret == false)
  {
    printf("insert user info parse json failed!\n");
    rsp.status=400;//Bad Request
    return;
  }
  //3.调用table_user中的Insert接口向数据库插入数据
  ret=table_user->Insert(root);
  if(ret == false)
  {
    printf("insert user info into db failed!\n");
    rsp.status=500;//服务器内部错误
    return;
  }
  //4.填充rsp响应信息
  rsp.status=200;
  return;
}
void DeleteUser(const httplib::Request &req,httplib::Response &rsp)
{
  //获取删除的用户id 
  //执行数据库操作
  //填充响应
  int user_id=std::stoi(req.matches[1]);//matches[0]放的是整个字符串,剩下的是捕捉到的
  
  bool ret=table_user->Delete(user_id);
  if(ret == false)
  {
    printf("delete user failed!!\n");
    rsp.status=500;
    return;
  }
  rsp.status=200;
  return;
}

void PutUser(const httplib::Request &req,httplib::Response &rsp)
{
  int user_id=std::stoi(req.matches[1]);
  std::string json_str=req.body;
  Json::Reader reader;
  Json::Value root;
  bool ret=reader.parse(json_str,root);
  if(ret == false)
  {
    printf("update user info,json format error\n");
    rsp.status=400;
    return;
  }
  ret=table_user->Update(user_id,root);
  if(ret == false)
  {
    printf("update user info,db operator error\n");
    rsp.status=500;
    return;
  }
  rsp.status=200;
  return;
}

void GetAllUser(const httplib::Request &req,httplib::Response &rsp)
{
  //从数据库获取到所有用户信息的Json::Value
  Json::Value root;
  bool ret=table_user->GetAll(&root);
  if(ret == false)
  {
    printf("get all user info,db operator error\n");
    rsp.status=500;
    return;
  }

  //将Json::Value转换为字符串，座位响应的正文
  Json::FastWriter writer;
  std::string body;
  body=writer.write(root);

  rsp.set_content(&body[0],body.size(),"application/json");
  return;

}
void GetOneUser(const httplib::Request &req,httplib::Response &rsp)
{
  int user_id=std::stoi(req.matches[1]);
  Json::Value root;
  bool ret=table_user->GetOne(user_id,&root);
  if(ret == false)
  {
    printf("get one user info,db operator error\n");
    rsp.status=500;
    return;
  }
  Json::FastWriter writer;
  rsp.set_content(writer.write(root),"application/json");
  return;
}

void InsertTag(const httplib::Request &req,httplib::Response &rsp)
{
  std::string json_str=req.body;
  Json::Reader reader;
  Json::Value root;
  bool ret=reader.parse(json_str,root);
  if(ret == false)
  {
    printf("insert tag info parse json failed!\n");
    rsp.status=400;//Bad Request
    return;
  }
  ret=table_tag->Insert(root);
  if(ret == false)
  {
    printf("insert tag info into db failed!\n");
    rsp.status=500;//服务器内部错误
    return;
  }
  rsp.status=200;
  return;
}
void DeleteTag(const httplib::Request &req,httplib::Response &rsp)
{
  int tag_id=std::stoi(req.matches[1]);
  bool ret=table_tag->Delete(tag_id);
  if(ret==false)
  {
    printf("delete tag info from db failed!!\n");
    rsp.status=500;
    return;
  }
  rsp.status=200;
  return;
}
void PutTag(const httplib::Request &req,httplib::Response &rsp)
{
  int tag_id=std::stoi(req.matches[1]);
  std::string json_str=req.body;
  Json::Reader reader;
  Json::Value root;
  bool ret=reader.parse(json_str,root);
  if(ret == false)
  {
    printf("update tag info parse json failed!\n");
    rsp.status=400;//Bad Request
    return;
  }
  ret=table_tag->Update(tag_id,root);
  if(ret==false)
  {
    printf("update tag info from db failed!!\n");
    rsp.status=500;
    return;
  }
  rsp.status=200;
  return;
}

void GetAllTag(const httplib::Request &req,httplib::Response &rsp)
{
  Json::Value root;
  bool ret=table_tag->GetAll(&root);
  if(ret == false)
  {
    printf("get all tag info from db failed!!\n");
    rsp.status=500;
    return; 
  }
  Json::FastWriter writer;
  rsp.set_content(writer.write(root),"application/json");
  return;
}
void GetOneTag(const httplib::Request &req,httplib::Response &rsp)
{
  int tag_id=std::stoi(req.matches[1]);
  Json::Value root;
  bool ret=table_tag->GetOne(tag_id,&root);
  if(ret == false)
  {
    printf("get one tag info from db failed!!\n");
    rsp.status=500;
    return; 
  }
  Json::FastWriter writer;
  rsp.set_content(writer.write(root),"application/json");
  return;
}

void InsertBlog(const httplib::Request &req,httplib::Response &rsp)
{
  std::string json_str=req.body;
  Json::Reader reader;
  Json::Value root;
  bool ret=reader.parse(json_str,root);
  if(ret == false)
  {
    printf("insert blog info parse json failed!\n");
    rsp.status=400;//Bad Request
    return;
  }
  ret=table_blog->Insert(root);
  if(ret == false)
  {
    printf("insert blog info into db failed!\n");
    rsp.status=500;//服务器内部错误
    return;
  }
  rsp.status=200; 
  return;
}

void DeleteBlog(const httplib::Request &req,httplib::Response &rsp)
{
  int blog_id=std::stoi(req.matches[1]);
  bool ret=table_blog->Delete(blog_id);
  if(ret==false)
  {
    printf("delete blog info from db failed!!\n");
    rsp.status=500;
    return;
  }
  rsp.status=200;
  return;
}

void PutBlog(const httplib::Request &req,httplib::Response &rsp)
{
  int blog_id=std::stoi(req.matches[1]);
  std::string json_str=req.body;
  Json::Reader reader;
  Json::Value root;
  bool ret=reader.parse(json_str,root);
  if(ret == false)
  {
    printf("update blog info parse json failed\n");
    rsp.status=400;
    return;
  }
   ret=table_blog->Update(blog_id,root);
  if(ret == false)
  {
    printf("update blog info from db failed!\n");
    rsp.status=500;
    return;
  }
  rsp.status=200;
  return;
}
void GetAllBlog(const httplib::Request &req,httplib::Response &rsp)
{
  Json::Value root;
  if(req.has_param("tag_id"))
  {
    int tag_id=std::stoi(req.get_param_value("tag_id"));
    bool ret=table_blog->GetTag(tag_id,&root);
    if(ret == false)
      {
        printf("get tag blog info from db failed!\n");
        rsp.status=500;
        return;
      }
  }
  else if(req.has_param("user_id"))
  {
    int user_id=std::stoi(req.get_param_value("user_id"));
    bool ret=table_blog->GetUser(user_id,&root);
    if(ret == false)
      {
        printf("get user blog info from db failed!\n");
        rsp.status=500;
        return;
      }
  }
  else{ 
    bool ret=table_blog->GetALL(&root);
    if(ret == false)
      {
        printf("get all blog info from db failed!\n");
        rsp.status=500;
        return;
      }
  }
  Json::FastWriter writer;
  rsp.set_content(writer.write(root),"application/json");
  return;
}
void GetOneBlog(const httplib::Request &req,httplib::Response &rsp)
{
  int blog_id=std::stoi(req.matches[1]);
  Json::Value root;
  bool ret=table_blog->GetBlog(blog_id,&root);
  if(ret==false)
  {
    printf("get one blog info from db failed!!\n");
    rsp.status=500;
    return;
  }
  Json::FastWriter writer;
  rsp.set_content(writer.write(root),"application/json");
  return;
}

int main(int argc,char *argv[])
{
  MYSQL *mysql=blog_system::MysqlInit();
  if(mysql == NULL)
  {
    return -1;
  }
  table_blog=new blog_system::TableBlog(mysql);
  table_tag=new blog_system::TableTag(mysql);
  table_user=new blog_system::TableUser(mysql);

  httplib::Server server;
  //设置url中的资源路径的相对根目录
  //好处:一些相对根目录下的静态文件资源,httplib会直接自动进行读取响应
  server.set_base_dir(WWWROOT);

  server.Post(R"(/user)",InsertUser);
  //R"()"--括号中的数据是原始数据，去除特殊字符的特殊含义
  //路由注册函数的第一个参数可以是一个正则表达式;
  server.Delete(R"(/user/(\d+))",DeleteUser);
  server.Put(R"(/user/(\d+))",PutUser);
  server.Get(R"(/user)",GetAllUser);
  server.Get(R"(/user/(\d+))",GetOneUser);

  server.Post(R"(/tag)",InsertTag);
  server.Delete(R"(/tag/(\d+))",DeleteTag);
  server.Put(R"(/tag/(\d+))",PutTag);
  server.Get(R"(/tag)",GetAllTag);
  server.Get(R"(/tag/(\d+))",GetOneTag);
  
  server.Post(R"(/blog)",InsertBlog);
  server.Delete(R"(/blog/(\d+))",DeleteBlog);
  server.Put(R"(/blog/(\d+))",PutBlog);
  server.Get(R"(/blog)",GetAllBlog);//get /blog-所有 /blog?tag_id=1 /blog?user_id=1
  server.Get(R"(/blog/(\d+))",GetOneBlog);

  server.listen("0.0.0.0",9000);
  blog_system::MysqlRelease(mysql);
  return 0;
}
