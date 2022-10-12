# dependency

gtkmm-4.0

```bash
sudo pacman -S --needed --noconfirm gtkmm-4.0
```

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

## List

```bash
curl -v -X GET http://127.0.0.1:8888/web/list
curl -v -X GET http://127.0.0.1:8888/web/list?before=124
```