
#define NL_MSG_SIZE 100

typedef struct {
  int link_speed;
  int duplex_mode;
} SWITCH_LINK_SPEED;

void encode_link_speed_nl_message(const SWITCH_LINK_SPEED* link_speed, char* nl_message) {
  sprintf(nl_message, "link_speed:%d,duplex_mode:%d", link_speed->link_speed, link_speed->duplex_mode);
}


In this code:

- `SWITCH_LINK_SPEED` is a structure that contains two fields: `link_speed` and `duplex_mode`.
- The `encode_link_speed_nl_message` function takes a pointer to a `SWITCH_LINK_SPEED` structure and a buffer `nl_message` to store the encoded NL message.
- The `sprintf` function is used to format the `link_speed` and `duplex_mode` values into the `nl_message` buffer as a string. The format of the string is `"link_speed:%d,duplex_mode:%d"`, where `%d` is a placeholder for the integer values.
- The resulting NL message will be stored in the `nl_message` buffer. The maximum size of the buffer is specified by the `NL_MSG_SIZE` constant.

You can call this function in your code like this:

c
SWITCH_LINK_SPEED link_speed = {1000, 1};
char nl_msg[NL_MSG_SIZE];

encode_link_speed_nl_message(&link_speed, nl_msg);
