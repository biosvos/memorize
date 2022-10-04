# example
## Add
```bash
curl -v -X POST http://127.0.0.1:8888/web/add \
   -H 'Content-Type: application/json' \
   -H 'Accept: application/json' \
   -d '{
  "word": "hi",
  "meanings": [
    "안녕"
  ],
  "time": 123
}'
```
## Update
```bash
curl -v -X PUT http://127.0.0.1:8888/web/update \
   -H 'Content-Type: application/json' \
   -H 'Accept: application/json' \
   -d '{
  "word": "hi",
  "meanings": [
    "안녕"
  ],
  "next_time": 555,
  "success": 3
}'
```