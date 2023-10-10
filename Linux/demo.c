struct data_pak {
        your_header_type header;
        hs_pak_t *pak;
        data_pak *next;
}


data_pak *g_pak_list = NULL;

int main() {

    /*pak来了，拷贝一份儿*/
    new_pak = pak_and_buf_copy(pak);

    /*你自己的pak链如果为空，为头结点分配空间，并将next设置为NULL*/
    if (g_pak_list == NULL) {
        g_pak_list = (data_pak*)malloc(sizeof(data_pak));
        g_pak_list->next = NULL;
    }
    /*用 p 记录当前节点*/
    data_pak *p = g_pak_list;
    data_pak tmp = NULL;

    /*遍历到末尾*/
    while(p->next) {
        p = p->next;
    }

    /*开辟一个你自己定义的节点空间*/
    tmp = (data_pak*)malloc(sizeof(data_pak));
    /*next 先设置为NULL，防止后面忘记*/
    tmp->next = NULL;
    /*链表尾指向 tmp*/
    p->next = tmp;

    /*p 移动到 tep*/
    p = tmp;
    /*给p里面的pak赋值*/
    p->pak = new_pak;

    ...
}