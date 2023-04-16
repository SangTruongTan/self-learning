#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Message {
public:
    Message() {}
    const string &get_text() {
        this->Text_ = this->Text_.substr(this->Text_.find("&&") + 2);
        return Text_;
    }
    void order(int num, const string &text) {
        string mText = text;
        char buf[255];
        sprintf(buf, "%d&&", num);
        Text_ = buf + mText;
    }
    bool operator<(Message &lhs) {
        int num1 = stoi(this->Text_.substr(0, this->Text_.find("&&")).c_str());
        int num2 = stoi(lhs.Text_.substr(0, lhs.Text_.find("&&")).c_str());
        return num1 < num2;
    }
    string Text_;
};

class MessageFactory {
public:
    MessageFactory() {}
    Message create_message(const string &text) {
        Message *msg = new Message();
        msg->order(num, text);
        num++;
        return *msg;
    }

private:
    int num = 0;
};

class Recipient {
public:
    Recipient() {}
    void receive(const Message &msg) { messages_.push_back(msg); }
    void print_messages() {
        fix_order();
        for (auto &msg : messages_) {
            cout << msg.get_text() << endl;
        }
        messages_.clear();
    }

private:
    void fix_order() { sort(messages_.begin(), messages_.end()); }
    vector<Message> messages_;
};

class Network {
public:
    static void send_messages(vector<Message> messages, Recipient &recipient) {
        // simulates the unpredictable network, where sent messages might arrive
        // in unspecified order
        random_shuffle(messages.begin(), messages.end());
        for (auto msg : messages) {
            recipient.receive(msg);
        }
    }
};

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    clock_t start = clock();
    MessageFactory message_factory;
    Recipient recipient;
    vector<Message> messages;
    string text;
    while (getline(cin, text)) {
        messages.push_back(message_factory.create_message(text));
    }
    Network::send_messages(messages, recipient);
    recipient.print_messages();
    clock_t end = clock();
    printf("Time taken:%lfs\r\n", (double) (end - start)/CLOCKS_PER_SEC);
}
