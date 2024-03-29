<?php

/** @generate-class-entries */

namespace Qshurick\Jq;

final class Jq {
    public function __construct() {}

    /**
     * @throws InvalidProgramException
     * @throws InvalidJsonStringException
     * @throws UnableTransformException
     */
    public function transform(string $program, string $jsonString): string {}
}

final class InvalidProgramException extends \RuntimeException {}
final class InvalidJsonStringException extends \RuntimeException {}
final class UnableTransformException extends \RuntimeException {}
