- AbilitySystemComponent
  - Foundation of GAS
- GameplayTag
  - various usage
    - state, tag, category, mutex, etc..
- GameplayAttribute
  - values used in game (field)
- GameplayAbility
  - things that actor can do
    - skill, action, craft, movement, etc..
- GameplayEffect
  - used by Ability to change Attributes permanently or temporally
- GameplayCue
  - visual, sound effects (not important for logic)
    - "GameplayCue" GameplayTag is essential
- AbilityTask
  - extended GameplayTask; sideeffects or parallel work of Ability


- ability add & remove
  - GiveAbility
    > add ability
  - GiveAbilityAndActivateOnce
    > try to execute and add ability
  - ClearAbility
    > remove ability right now
  - SetRemoveAvilityOnEnd
    > reserve ClearAbility after activation
  - ClearAllAbility
    > remove all abilities right now : doesnt need handle


- ability execution
  - CanActivateAbility
    > check is it available, not execute
  - CallActivateAbility
    > execute ability without check
  - ActivateAbility
  - CommitAbility
  - CancelAbility
  - TryActivateAbility
  - EndAbility
  

- tag query
  - CancelAbilitesWithTag
    > BETA with TAG canceled when ALPHA activated
  - BlockAbilitiesWithTag
    > BETA with TAG blocked when ALPHA is activating
  - ActivationOwnedTags
    > USER get TAGS when ALPHA is activating
  - ActivationRequiredTags
    > ALPHA can't be activated if USER don't have  every TAGS
  - ActivationBlockedTags
    > ALPHA can't be activated if USER have any of TAGS
  - TargetRequiredTags
    > ALPHA can't be activated if TARGET don't have every TAGS
  - TargetBlockedTags
    > ALPHA can't be activated if TARGET have any of TAGS