# Plagiarism Detector

A C++ command-line tool that detects plagiarism between text documents by combining two independent similarity measures: rolling-hash containment similarity and Longest Common Subsequence (LCS) similarity.

## How It Works

1. **Text Normalization** — Each document's raw text is cleaned: punctuation and whitespace are stripped, and all characters are lowercased, leaving a continuous alphanumeric string.

2. **Rolling Hash Fingerprinting** — A sliding window (size 10) generates a Rabin-Karp style rolling hash over the cleaned text. Each unique window hash is stored in a set, creating a fingerprint of the document's content chunks.

3. **Similarity Scoring** — Two documents are compared using two separate metrics:
   - **Hash containment similarity** — `common hashes / size of smaller hash set`. Catches reused chunks of text regardless of order.
   - **LCS similarity** — Longest Common Subsequence between the two cleaned texts, normalized by the shorter document's length. Catches sequence-preserving plagiarism (e.g. light paraphrasing, word substitution).

   The two scores are averaged into a single combined score, which is compared against a configurable threshold to flag plagiarism.

## Project Structure

```
main.cpp                  Entry point, menu-driven CLI
FileManager.h/.cpp        Reads file contents from disk
TextNormalization.h/.cpp  Cleans and lowercases raw text
Document.h/.cpp           Wraps a document, computes rolling hash fingerprints
PlagiarismDetector.h/.cpp Compares documents using hash + LCS similarity
```

### Dependency Graph

```
main.cpp
 ├── FileManager.h
 └── PlagiarismDetector.h
      └── Document.h
           └── TextNormalization.h (used internally by Document.cpp)
```

## Building

Compile all source files together:

```bash
g++ -o plagiarism main.cpp FileManager.cpp TextNormalization.cpp Document.cpp PlagiarismDetector.cpp
```

## Running

```bash
./plagiarism
```

Place `doc1.txt`, `doc2.txt`, and `doc3.txt` in the same directory as the compiled binary. The program loads all three, then presents a menu:

```
1. Direct Check (Document 1 vs Document 2)
2. Check All
Enter choice:
```

- **Option 1** — Runs a direct comparison between the first two documents and prints the hash/LCS/combined score breakdown.
- **Option 2** — Compares every pair of loaded documents and reports any pair whose combined score meets or exceeds the threshold.

## Example Output

```
Loaded: doc1.txt
Loaded: doc2.txt
Loaded: doc3.txt

1. Direct Check (Document 1 vs Document 2)
2. Check All
Enter choice: 1

--- Direct Check: Document 1 vs Document 2 ---
  Hash similarity: 80%
  LCS similarity:  98.2005%
  Combined score:  89.1003%
Plagiarism detected between Document 1 and Document 2.
```

## Design Notes

- **Why two similarity metrics instead of one?** Hash containment is order-independent and catches reshuffled or copy-pasted chunks. LCS is order-sensitive and catches paraphrased text where word order is mostly preserved. Combining both gives broader detection coverage than either alone.
- **Why containment instead of Jaccard similarity for hashes?** Jaccard (`common / union`) penalizes documents that differ in length, even when the overlapping content is identical — a single inserted or removed phrase can shift every subsequent hash window out of phase, causing a false drop in similarity. Containment (`common / min(size_a, size_b)`) is more robust to this.
- **Known limitation — LCS is character-level, not word-level.** This means common substrings inside unrelated words (e.g. `"ing"`, `"the"`, `"tion"`) can contribute to a non-zero similarity score even between unrelated documents. A word-level LCS with stop-word removal would tighten this further but was out of scope for this version.
- **Combined score is a simple average.** This is easy to reason about but dilutes either signal when only one metric detects copying strongly (e.g. heavily reordered plagiarism scores high on hash but lower on LCS). A weighted average or `max()` of the two scores are reasonable alternatives depending on whether precision or recall is prioritized.

## Possible Extensions

- Word-level tokenization with stop-word removal for a sharper LCS signal
- Configurable window size and similarity weights via command-line flags
- Support for comparing more than 3 documents via dynamic file discovery
- Sentence-level plagiarism localization (which specific sentences matched)
