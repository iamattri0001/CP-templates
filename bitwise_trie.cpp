class Trie{
    const int BIT = 20;
    struct Node{
        Node *links[2];
        int cnt;
        Node() {
            links[0] = links[1] = nullptr;
            cnt = 0;
        }
    };

    Node *root;
    stack<Node*> st;

    Node *get_new_node() {
        if(st.empty())
            return new Node();

        auto ptr = st.top();
        st.pop();
        return ptr;
    }

public:
    Trie() {
        root = new Node();
    }

    void insert(int num) {
        auto ptr = root;
        for(int i = BIT-1; i >= 0; i--) {
            bool b = (num & (1<<i));
            if(!ptr->links[b])
                ptr->links[b] = get_new_node();
            ptr = ptr->links[b];
            ptr->cnt++;
        }
    }

    bool find(int num) {
        auto ptr = root;
        for(int i = BIT-1; i >= 0; i--) {
            bool b = (num & (1<<i));
            if(!ptr->links[b] && ptr->links[b])
                return 0;
            ptr = ptr->links[b];
        }
        return 1;
    }

    bool erase(int num) {
        auto ptr = root;
        vector<Node*> to_delete;
        Node *par = nullptr;
        for (int i = BIT - 1; i >= 0; i--) {
            bool b = (num & (1 << i));
            par = ptr;
            ptr = ptr->links[b];
            ptr->cnt--;
            if(ptr->cnt == 0) {
                par->links[b] = nullptr;
                to_delete.push_back(ptr);
            }
        }

        for(auto &it: to_delete) {
            it->links[0] = it->links[1] = nullptr;
            it->cnt = 0;
            st.push(it);
        }

        return 1;
    }


    int xorMax(int num) {
        int ans = 0;
        auto ptr = root;
        for(int i = BIT-1; i >= 0; i--) {
            bool b = (num & (1<<i));
            b = (!b); //opposite bit

            if(ptr->links[b]) {
                ans |= (1<<i);
                ptr = ptr->links[b];
            } else {
                ptr = ptr->links[!b];
            }
        }
        return ans;
    }
};
