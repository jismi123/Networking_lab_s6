write(c_sock, buff2, sizeof(buff2));
    usleep(1000);
    i = i + 1;
    bzero(buff2, sizeof(buff2));
    strcpy(buff2, msg);
    buff2[strlen(msg)] = i + '0';
    printf("Message sent to client :%s \n", buff2);
    write(c_sock, buff2, sizeof(buff2));
    i = i + 1;
    usleep(1000);
qqq:
    bzero(buff2, sizeof(buff2));
    strcpy(buff2, msg);
    buff2[strlen(msg)] = i + '0';
    printf("Message sent to client :%s \n", buff2);
    write(c_sock, buff2, sizeof(buff2));
    FD_ZERO(&set1);
    FD_SET(c_sock, &set1);
    timeout1.tv_sec = 2;
    timeout1.tv_usec = 0;

    rv1 = select(c_sock + 1, &set1, NULL, NULL, &timeout1);
    if (rv1 == -1)
        perror("select error ");
    else if (rv1 == 0)
    {
        printf("Going back from %d:timeout \n", i);
        i = i - 3;
        goto qq;
    }
    else
    {
        read(c_sock, buff, sizeof(buff));
        printf("Message from Client: %s\n", buff);
        i++;
        if (i <= 9)
            goto qqq;
    }
qq2:
    FD_ZERO(&set2);
    FD_SET(c_sock, &set2);
    timeout2.tv_sec = 3;
    timeout2.tv_usec = 0;
    rv2 = select(c_sock + 1, &set2, NULL, NULL, &timeout2);
    if (rv2 == -1)
        perror("select error ");
    else if (rv2 == 0)
    {
        printf("Going back from %d:timeout on last 2\n", i - 1);
        i = i - 2;
        bzero(buff2, sizeof(buff2));
        strcpy(buff2, msg);
        buff2[strlen(buff2)] = i + '0';
        write(c_sock, buff2, sizeof(buff2));
        usleep(1000);
        bzero(buff2, sizeof(buff2));
        i++;
        strcpy(buff2, msg);
        buff2[strlen(buff2)] = i + '0';
        write(c_sock, buff2, sizeof(buff2));
        goto qq2;
    }
    else
    {
        read(c_sock, buff, sizeof(buff));
        printf("Message from Client: %s\n", buff);
        bzero(buff, sizeof(buff));
        read(c_sock, buff, sizeof(buff));
        printf("Message from Client: %s\n", buff);
    }

    close(c_sock);
    close(s_sock);
    return 0;
}
