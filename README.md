# SHA-2 Implementation in C

This project provides a robust and efficient implementation of the SHA-2 cryptographic hash function in C, specifically targeting the SHA-256 and SHA-512 variants. Designed for simplicity and performance, it\'s a great starting point for anyone looking to understand or utilize cryptographic hashing in their applications.

## Features

- **Efficient C Implementation**: Optimized for performance and memory usage.
- **Multiple Variants**: Support for SHA-256 and SHA-512.
- **Easy Integration**: Simple API for easy integration into other projects.
- **Comprehensive Testing**: Includes a suite of unit tests for validation.

## Getting Started

### Prerequisites

- GCC or any standard C compiler
- Make (for building the project)

### Installation

Clone the repository:

```bash
git clone https://github.com/yourusername/sha2-implementation.git
cd sha2-implementation
```

Build the project:

```bash
make all
```

### Usage

To use the SHA-2 implementation in your C project, include the header file and link the library:

```c
#include "sha2.h"
```

## Code Examples

Here\'s a simple example of how to use the SHA-256 implementation:

```c
#include "sha2.h"

int main() {
    const char *message = "Hello, World!";
    unsigned char hash[SHA256_BLOCK_SIZE];

    sha256((unsigned char*)message, strlen(message), hash);

    printf("SHA-256: ");
    for (int i = 0; i < SHA256_BLOCK_SIZE; i++)
        printf("%02x", hash[i]);
    printf("\\n");

    return 0;
}
```

## Testing

Run the included test suite to validate the implementation:

```bash
make test
```

## Documentation

For more information, see the `/docs` directory.

## Contributing

Contributions to this project are welcome. Please submit pull requests or issues through the GitHub repository.

## License

This project is licensed under the MIT License - see the `LICENSE` file for details.

## Acknowledgments

- Thanks to all contributors and supporters of the project.
