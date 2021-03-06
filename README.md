safenet-mysql
=============

SafeNet for MySQL - http://www.safenet-inc.com/

Installation Plugin
------------
    yum install -y libcurl-devel

    cd src
    cmake .
    make 
    make install

    cat > /etc/sysconfig/mysqld <<EOF
    export SAFENET_URL=http://host.localdomain/safe/interface
    export SAFENET_KEY=Web01-key
    EOF

Create Function
---------------------
    create function safenet_encrypt returns string soname 'libsafenet.so';
    create function safenet_decrypt returns string soname 'libsafenet.so';
    create function safenet_config returns string soname 'libsafenet.so';

Example
-------
    mysql> select safenet_encrypt('Helloworld!!!');
    +----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
    | safenet_encrypt('Helloworld!!!')                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 |
    +----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
    | 994BAB7BC417F0559A09ECE94EDCB695AC1D5705F7ABA9F3562158F5AFAC4720FA9B3E53F30DF65C1726E0F02A93A9CAE7E486349F41AE4F504DC2B49F809C5AF77FEF4DE49D03D8DEC4000B15F2F2A2296500AA6159491E65DEFDFE75FB2E79D31D9BF0CC67932ADA212C34C0B04BF30F222102FAD857F440404C0FE92B8626EA3126B0B5A4FA0B1D09F1CC9EF45EBB6A72123AE82D39F659C717A5AA4F7FB5BDBBC7977C7021F61BBC26B9DB78C9A8657C6BC291CAE5C07F9DF485D71A1E9CC8888793B03BB5AF2DDB57AAEFB6D2EA569226651092414F96BA0880B35B0D8A01A1F7B82C308A2316D07C0FD4E0A298ECB33F4E4EB9F1A1E53760B0BFBE7449 |
    +----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
    1 row in set (0.58 sec)

    mysql> select safenet_decrypt(safenet_encrypt('Helloworld!!!'));
    +---------------------------------------------------+
    | safenet_decrypt(safenet_encrypt('Helloworld!!!')) |
    +---------------------------------------------------+
    | Helloworld!!!                                     |
    +---------------------------------------------------+
    1 row in set (0.31 sec)

	mysql> select safenet_config();

Drop Function
-------------
    drop function safenet_encrypt;
    drop function safenet_decrypt;
    drop function safenet_config;

-----

You also can use make to compile.
---------------------------------
    ./configure --prefix=/usr/lib64/mysql --libdir=/usr/lib64/mysql/plugin --with-mysql=/usr/bin/mysql_config
    make
    make insall

    cat > /etc/sysconfig/mysqld <<EOF
    export SAFENET_URL=http://host.localdomain/safe/interface
    export SAFENET_KEY=Web01-key
    EOF

    create function safenet_encrypt returns string soname 'safenet.so';
    create function safenet_decrypt returns string soname 'safenet.so';
    create function safenet_config returns string soname 'safenet.so';

    drop function safenet_encrypt;
    drop function safenet_decrypt;
    drop function safenet_config;


[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/netkiller/mysql-safenet-plugin/trend.png)](https://bitdeli.com/free "Bitdeli Badge")

