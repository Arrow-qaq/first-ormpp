     #修改加密规则  
    ALTER USER 'root'@'localhost' IDENTIFIED BY 'password' PASSWORD EXPIRE NEVER; 
    #更新密码（mysql_native_password模式）    
    ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'Hovertree';