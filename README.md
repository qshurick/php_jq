# PHP_JQ

Php extension that integrates with JQ library to bring great experience of working with JSON data in PHP.

It is stil under development, and many bugs are expected, be cautious when use.

## Installation

Tested on linux

1. Clone the repository
2. Install required dependencies: jq
3. Build and install the project
   Note: in current ubuntu distribution libjq missing some package description (.pc file), to build correctly the environment variables `LIBJQ_CFLAGS` and `LIBJQ_LIBS` need to be set
4. Add extension in `php.ini`

```shell
apt-get update
apt-get install jq
git clone
cd php_jq
phpize
LIBJQ_CFLAGS="-I/usr/includes" LIBJQ_LIBS="-ljq" ./configure
make
make test
make install
```

Now extension should be available.

## Example

### Extract data from JSON

```php
<?php

declare(strict_types=1);

use Qshurick\Jq\Jq;

$jq = new Jq();
$json = <<<JSON
    {
        "data": {
            "me": {
                "shoppingCart": {
                    "products": [
                        {
                            "id": 1,
                            "title": "Awesonme product",
                            "price": {
                                "value": 1234,
                                "currency": "EUR"
                            }
                        }
                    ]
                }
            }
        }
    }
JSON;

var_dump($jq->transform(".data.me.shoppingCart.products", $json));

// string(77) "[{"id":1,"title":"Awesonme product","price":{"value":1234,"currency":"EUR"}}]"}}
```

### Transform JSON to different shape

```php
<?php

declare(strict_types=1);

use Qshurick\Jq\Jq;

$jq = new Jq();
$json = <<<JSON
    {
        "id": 42,
        "flad": true,
        "list": [0, 1, 2, 3],
        "hello": "world"
    }
JSON;

var_dump($jq->transform('{custome_id:.id,list:.list|map(.*3),(.hello):(if .flag then "hi" else "hey" end)}', $json));

// string(48) "{"custome_id":42,"list":[0,3,6,9],"world":"hey"}"}
```

For more information on JQ program syntax see [JQ manual](https://jqlang.github.io/jq/manual/)
