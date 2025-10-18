#!/bin/bash

echo "🔍 Running PR validation checks..."

# Initialize validation status
validation_failed=false

# Get list of changed files
if [ -z "$GITHUB_EVENT_PATH" ]; then
    echo "Not running in GitHub Actions, skipping file detection"
    exit 0
fi

# Extract changed files from GitHub event
changed_files=$(jq -r '.pull_request.changed_files[]?.filename // empty' "$GITHUB_EVENT_PATH" 2>/dev/null)

if [ -z "$changed_files" ]; then
    echo "No changed files detected"
    exit 0
fi

echo "📁 Changed files:"
echo "$changed_files"
echo ""

# Check file naming conventions
echo "📝 Checking file naming conventions..."
invalid_files=()

while IFS= read -r file; do
    if [ -z "$file" ]; then continue; fi

    echo "Checking: $file"
    filename=$(basename "$file")
    dir=$(dirname "$file")

    # Check naming conventions based on file extension (Allow flexible naming)
    case "$file" in
        *.c|*.cpp|*.py)
            # Allow snake_case, camelCase, or PascalCase for C/C++/Python
            if [[ ! "$filename" =~ ^[a-zA-Z0-9_]+\.[a-z]+$ ]]; then
                invalid_files+=("$file: Use alphanumeric characters and underscores only (e.g., binary_search.cpp, maxRectangle.cpp)")
            fi
            ;;
        *.java)
            # Should use PascalCase for Java classes
            if [[ ! "$filename" =~ ^[A-Z][a-zA-Z0-9]*\.java$ ]]; then
                invalid_files+=("$file: Java files should use PascalCase (e.g., BinarySearch.java, MaxRectangle.java)")
            fi
            ;;
        *.js|*.ts|*.go|*.rs|*.kt|*.swift|*.php|*.rb|*.cs|*.dart|*.scala)
            # Allow flexible naming for other languages
            if [[ ! "$filename" =~ ^[a-zA-Z0-9_]+\.[a-z]+$ ]]; then
                invalid_files+=("$file: Use alphanumeric characters and underscores only")
            fi
            ;;
    esac

    # Check directory structure - must be in Language/Category or Language/Category/Subcategory
    if [[ "$file" =~ \.(c|cpp|java|py|js|ts|go|rs|kt|swift|php|rb|cs|dart|scala)$ ]]; then
        # Check if file is in a valid language directory with at least one subdirectory
        if [[ ! "$dir" =~ ^(C|CPP|Java|Python|JavaScript|TypeScript|Go|Rust|Kotlin|Swift|PHP|Ruby|CSharp|Dart|Scala)/ ]]; then
            invalid_files+=("$file: Must be in a language directory (C/, CPP/, Java/, Python/, etc.)")
        elif [[ ! "$dir" =~ (algorithms|data_structures|dynamic_programming|projects) ]]; then
            invalid_files+=("$file: Should be in proper category (algorithms/, data_structures/, dynamic_programming/, or projects/)")
        fi
    fi
done <<< "$changed_files"

if [ ${#invalid_files[@]} -gt 0 ]; then
    echo "❌ Found naming/structure violations:"
    printf '%s\n' "${invalid_files[@]}"
    validation_failed=true
else
    echo "✅ All files follow naming conventions!"
fi

# Check for required documentation
echo ""
echo "📚 Checking for documentation..."
missing_docs=()

while IFS= read -r file; do
    if [ -z "$file" ]; then continue; fi

    if [[ "$file" =~ \.(c|cpp|java|py|js|ts|go|rs|kt|swift|php|rb|cs|dart|scala)$ ]]; then
        if [ -f "$file" ]; then
            echo "Checking documentation in: $file"

            # Check for basic documentation elements
            if ! grep -q -i "algorithm\|description\|complexity\|time\|space" "$file" 2>/dev/null; then
                missing_docs+=("$file: Missing algorithm description or complexity analysis")
            fi

            # Check for comments
            if ! grep -q -E "//|#|\*|--|<!--" "$file" 2>/dev/null; then
                missing_docs+=("$file: Missing comments")
            fi
        fi
    fi
done <<< "$changed_files"

if [ ${#missing_docs[@]} -gt 0 ]; then
    echo "⚠️ Found documentation issues:"
    printf '%s\n' "${missing_docs[@]}"
    echo ""
    echo "💡 Please add:"
    echo "  - Algorithm description"
    echo "  - Time/Space complexity"
    echo "  - Comments explaining the code"
    # Don't fail for missing docs, just warn
else
    echo "✅ Documentation looks good!"
fi

# Final result
if [ "$validation_failed" = true ]; then
    echo ""
    echo "❌ Validation failed. Please fix the issues above."
    exit 1
else
    echo ""
    echo "✅ All validation checks passed!"
    exit 0
fi