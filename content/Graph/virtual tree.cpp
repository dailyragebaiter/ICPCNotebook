function build_virtual_tree(U):
    // B1: thêm tất cả LCA vào U
    sort U theo in[u]
    for i = 0 → |U|-2:
        U.push( lca(U[i], U[i+1]) )
    
    // B2: loại bỏ trùng lặp
    sort U theo in[u]
    U.erase_duplicates()

    // B3: dựng cây bằng stack
    create empty stack st
    clear adjacency list mini_adj

    st.push(U[0])
    for i = 1 → |U|-1:
        while !is_ancestor(st.top(), U[i]):
            st.pop()
        mini_adj[st.top()].push_back(U[i])
        st.push(U[i])

    return U[0]   // root của cây ảo