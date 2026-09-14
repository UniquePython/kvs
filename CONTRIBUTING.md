# Contributing

## Versioning

kvs is versioned under [BFIP Versioning](https://github.com/UniquePython/bfip-versioning)
(B.F.I.P), not SemVer. Given a version `B.F.I.P`:

- **B**; the public API changed in a way that breaks existing user code
- **F**; new functionality was added to the public API; existing code still works
- **I**; implementation changed (perf, structure, dependencies); public API untouched
- **P**; a known bug was fixed; public API untouched

The project is currently in **breaking version zero** (`0.f.i.p`). Nothing
about the API is a stability promise yet.

**Public API: TBD.** No public API has been declared yet. It must be
declared no later than the transition to `1.0.0.0` (BFIP Rule 7); that
transition is exactly the act of declaring it for the first time. Until
then, B/F/I/P still increment and reset per the normal rules, but purely
for bookkeeping; none of it carries a compatibility guarantee.

## Branching model

- `main` only receives commits at release points, as a **squash commit**
 ; never direct development work, and never a full merge preserving a
  branch's individual commits. The pre-versioning setup commits on `main`
  (before any branch or tag existed) are the sole exception; from the
  first `0.1` branch onward, this rule is in force.
- `main`'s history is a flat release ledger: one commit per release, not
  a record of how that release was actually built. The detailed,
  commit-by-commit development history lives permanently on the B.F
  branch itself, and is never replicated into `main`.
- One long-lived branch per **B.F** pair (e.g. `0.1`, `0.2`, `1.0`).
  All I and P bumps for that line happen as ordinary commits on the same
  branch; I and P never get their own branch, since neither represents
  a new lineage, just a corrected or re-implemented state of the same one.
- A new B.F branch is created only on an F or B bump, forked from the
  **current tip of the branch it's incrementing from**; never from
  `main`. `main`'s tip may not reflect the latest state of the line
  you're working on, especially once multiple B.F lines are active in
  parallel.
- Old B.F branches stay alive after a newer one ships. They may keep
  receiving I/P commits (e.g. backported fixes) independently, per
  BFIP Rule 12, which allows different B.F lines to maintain their own
  I.P history concurrently with no required ordering between lines.

## Commit conventions

Development commits, made on a B.F branch, use one of exactly four prefixes:

- `chore:` — repo maintenance, tooling, config; nothing about the program
- `docs:` — documentation only
- `build:` — build system, Makefile, packaging
- `code:` — anything touching the actual program's source

Commit prefixes do **not** predict or encode the eventual B/F/I/P bump.
Classification is a release-level decision, made once, at tag time, by
looking at the net effect of everything since the last tag on that
branch.

A fifth prefix, `dev:`, is reserved exclusively for the single squash
commit that lands a release on `main` (see "Cutting a release" below).
It never appears on a B.F branch.

## Cutting a release

1. Make sure the branch you're releasing from is in the state you want
   tagged.
2. Decide the bump: did the public API break (B), gain something (F),
   change internally only (I), or get a bug fix (P)? Use whichever is
   highest if more than one applies; a higher-field bump already
   resets everything below it.
3. If this is a new B.F line, branch it now from the tip of the line
   it's coming from (not from `main`), if not already done.
4. `git checkout main`
5. `git merge --squash <branch>`
6. `git commit -m "dev: <B.F.I.P> development complete"`
7. `git tag <B>.<F>.<I>.<P>`
8. `git push origin main --tags`
9. Update `CHANGELOG.md` (once one exists) and, if this bump is worth
   announcing, cut a GitHub Release on the new tag; not every tag needs
   a Release page, but every bump needs a tag.
