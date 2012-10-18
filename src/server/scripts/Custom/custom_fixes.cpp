#include "ScriptMgr.h"


enum TrickOrTreat
{
    SPELL_TRICKY_TREAT_SPEED    = 42919,
    SPELL_TRICKY_TREAT_TRIGGER  = 42965,
    SPELL_UPSET_TUMMY           = 42966,
};

class spell_gen_tricky_treat : public SpellScriptLoader
{
    public:
        spell_gen_tricky_treat() : SpellScriptLoader("spell_gen_tricky_treat") {}

        class spell_gen_tricky_treat_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_gen_tricky_treat_SpellScript);

            bool Validate(SpellInfo const* /*spellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_TRICKY_TREAT_SPEED))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_TRICKY_TREAT_TRIGGER))
                    return false;
                if (!sSpellMgr->GetSpellInfo(SPELL_UPSET_TUMMY))
                    return false;
                return true;
            }

            void HandleScript(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                    if (caster->HasAura(SPELL_TRICKY_TREAT_TRIGGER) && caster->GetAuraCount(SPELL_TRICKY_TREAT_SPEED) > 3 && roll_chance_i(33))
                        caster->CastSpell(caster, SPELL_UPSET_TUMMY, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_gen_tricky_treat_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_gen_tricky_treat_SpellScript();
        }
};

void AddSC_custom_fixes()
{
    new spell_gen_tricky_treat();
}
