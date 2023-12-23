# SHA-2 Implementation in C

This project provides a robust and efficient implementation of the SHA-2 cryptographic hash function in C, specifically targeting the SHA-256 and SHA-512 variants. Designed for simplicity and performance, it\'s a great starting point for anyone looking to understand or utilize cryptographic hashing in their applications.

# Project File Structure

This section outlines the structure of the project files and directories, providing a clear overview of where each component of the SHA-2 implementation is located.

```
SHA-2-Implementation/
├── src/
│   ├── sha2.c               - Main SHA-2 algorithm implementation.
│   └── sha2_utils.c         - Utility functions for the SHA-2 algorithm.
│
├── include/
│   ├── sha2.h               - Header file for sha2.c.
│   └── sha2_utils.h         - Header file for sha2_utils.c.
│
├── tests/
│   ├── test_sha256.c        - Test cases for the SHA-256 algorithm.
│   └── test_sha512.c        - Test cases for the SHA-512 algorithm.
│
├── examples/
│   └── example_usage.c      - Example usage of the SHA-2 implementation.
│
├── docs/
│   └── Documentation files and additional resources.
│
├── build/
│   └── Compiled binaries and object files (excluded from source control).
│
├── .vscode/
│   ├── settings.json        - Custom settings for Visual Studio Code.
│   ├── launch.json          - Debugger configuration.
│   └── tasks.json           - Build tasks configuration.
│
├── Makefile or CMakeLists.txt
│   └── Build automation scripts.
│
├── .gitignore
│   └── Specifies intentionally untracked files to ignore.
│
├── README.md
│   └── Project overview and documentation.
│
└── LICENSE
    └── The license under which the project is released.
```

This file structure is designed to be clear and modular, allowing easy access to different parts of the project. It also supports best practices in software development, such as separation of source and header files, inclusion of tests and examples, and comprehensive documentation.


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
